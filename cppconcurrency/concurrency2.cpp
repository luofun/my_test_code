#include<list>
#include<mutex>
#include<algorithm>
#include <iostream>
#include <deque>
#include <exception>
#include <memory>
#include<stack>
#include <stdexcept>
#include <boost/thread/shared_mutex.hpp>
#include <map>
#include<boost\thread\locks.hpp>


std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

void test1()
{
	add_to_list(42);
	std::cout << "contains(1)=" << list_contains(1) << ", contains(42)=" << list_contains(42) << std::endl;
}

class some_data
{
	int a;
	std::string b;
public:
	void do_something()
	{
		std::cout << "test\n";
	}
};

class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		func(data);
	}
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
	x.process_data(malicious_function);
	unprotected->do_something();
}

template<typename T,typename Container=std::deque<T>>
class stack
{
public:
	explicit stack(const Container&);
	explicit stack(Container&& = Container());
	template<class Alloc> explicit stack(const Alloc&);
	template<class Alloc> stack(const Container&, const Alloc&);
	template<class Alloc> stack(Container&&, const Alloc&);
	template<class Alloc> stack(stack&&, const Alloc&);
	bool empty() const;
	size_t size() const;
	T& top();
	T const& top() const;
	void push(T const&);
	void push(T&&);
	void pop();
	void swap(stack&&);

private:

};


struct empty_stack : std::exception
{
	const char* what() const throw()
	{
		return "empty stack";
	}

};

template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;
public:
	threadsafe_stack(){}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data;
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = data.top();
		data.pop();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};


void test2(){
	threadsafe_stack<int> si;
	si.push(5);
	si.pop();
	if (!si.empty())
	{
		int x;
		si.pop(x);
	}

}

class some_big_object
{};

void swap(some_big_object& lhs, some_big_object& rhs)
{}

class X
{
private:
	some_big_object some_detail;
	mutable std::mutex m;
public:
	X(some_big_object const& sd) :some_detail(sd){}

	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		swap(lhs.some_detail, rhs.some_detail);
	}
};

class hierarchical_mutex
{
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;
	unsigned long previous_hierarchy_value;
	static int thread_local;
	unsigned long this_thread_hierarchy_value;

	void check_for_hierarchy_violation()
	{
		if (this_thread_hierarchy_value <= hierarchy_value)
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}
	void update_hierarchy_value()
	{
		previous_hierarchy_value = this_thread_hierarchy_value;
		this_thread_hierarchy_value = hierarchy_value;
	}
public:
	explicit hierarchical_mutex(unsigned long value) :
		hierarchy_value(value),
		previous_hierarchy_value(0)
	{}
	void lock()
	{
		check_for_hierarchy_violation();
		internal_mutex.lock();
		update_hierarchy_value();
	}
	void unlock()
	{
		this_thread_hierarchy_value = previous_hierarchy_value;
		internal_mutex.unlock();
	}
	bool try_lock()
	{
		check_for_hierarchy_violation();
		if (!internal_mutex.try_lock())
			return false;
		update_hierarchy_value();
		return true;
	}
};



hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff()
{
	return 42;
}


int low_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
	return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{}


void high_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
	high_level_stuff(low_level_func());
}

void thread_a()
{
	high_level_func();
}

hierarchical_mutex other_mutex(100);
void do_other_stuff()
{}


void other_stuff()
{
	high_level_func();
	do_other_stuff();
}

void thread_b()
{
	std::lock_guard<hierarchical_mutex> lk(other_mutex);
	other_stuff();
}

void test3(){
	hierarchical_mutex m1(42);
	hierarchical_mutex m2(2000);
}


class some_big_object2
{};

void swap(some_big_object2& lhs, some_big_object2& rhs)
{}

class X2
{
private:
	some_big_object2 some_detail;
	mutable std::mutex m;
public:
	X2(some_big_object2 const& sd) :some_detail(sd){}

	friend void swap(X2& lhs, X2& rhs)
	{
		if (&lhs == &rhs)
			return;
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
		std::lock(lock_a, lock_b);
		swap(lhs.some_detail, rhs.some_detail);
	}
};

void do_something(){
	std::cout << "hello\n";

}

std::unique_lock<std::mutex> get_lock(){
	extern std::mutex some_mutex;
	std::unique_lock<std::mutex> lk(some_mutex);
	//prepare_data();
	return lk;
}

void process_data(){
	std::unique_lock<std::mutex> lk(get_lock());
	do_something();

}

std::mutex the_mutex;

void get_and_process_data(){
	std::unique_lock<std::mutex> my_lock(the_mutex);
	//some_class_data_to_process = get_next_data_chunk();
	my_lock.unlock();
	//result_type =...
	my_lock.lock();
	//write_result

}

class Y
{
private:
	int some_detail;
	mutable std::mutex m;

	int get_detail() const
	{
		std::lock_guard<std::mutex> lock_a(m);
		return some_detail;
	}
public:
	Y(int sd) :some_detail(sd){}

	friend bool operator==(Y const& lhs, Y const& rhs)
	{
		if (&lhs == &rhs)
			return true;
		int const lhs_value = lhs.get_detail();
		int const rhs_value = rhs.get_detail();
		return lhs_value == rhs_value;
	}
};

struct some_resource
{
	void do_something()
	{}

};


std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void test4()
{
	std::unique_lock<std::mutex> lk(resource_mutex);
	if (!resource_ptr)
	{
		resource_ptr.reset(new some_resource);
	}
	lk.unlock();
	resource_ptr->do_something();
}

std::once_flag resource_flag;

void init_resource(){
	resource_ptr.reset(new  some_resource);

}

void test5(){
	std::call_once(resource_flag, init_resource);
	resource_ptr->do_something();
}

struct connection_info
{};

struct data_packet
{};

struct connection_handle
{
	void send_data(data_packet const&)
	{}
	data_packet receive_data()
	{
		return data_packet();
	}
};

struct remote_connection_manager
{
	connection_handle open(connection_info const&)
	{
		return connection_handle();
	}
} connection_manager;


class X3
{
private:
	connection_info connection_details;
	connection_handle connection;
	std::once_flag connection_init_flag;

	void open_connection()
	{
		connection = connection_manager.open(connection_details);
	}
public:
	X3(connection_info const& connection_details_) :
		connection_details(connection_details_)
	{}
	void send_data(data_packet const& data)
	{
		std::call_once(connection_init_flag, &X3::open_connection, this);
		connection.send_data(data);
	}
	data_packet receive_data()
	{
		std::call_once(connection_init_flag, &X3::open_connection, this);
		return connection.receive_data();
	}
};

class dns_entry
{};

class dns_cache
{
	std::map<std::string, dns_entry> entries;
	boost::shared_mutex entry_mutex;
public:
	dns_entry find_entry(std::string const& domain)
	{
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		std::map<std::string, dns_entry>::const_iterator const it =
			entries.find(domain);
		return (it == entries.end()) ? dns_entry() : it->second;
	}
	void update_or_add_entry(std::string const& domain,
		dns_entry const& dns_details)
	{
		std::lock_guard<boost::shared_mutex> lk(entry_mutex);
		entries[domain] = dns_details;
	}
};


void main(){
	
	//foo();
	//test2();
	//test3();
	test5();

}
