#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<thread>
#include<string>
#include<memory>
#include<vector>
#include<algorithm>
#include<functional>
#include <numeric>

void hello1()
{
	std::cout << "hello\n";
}

void hello2(int i){
	std::cout << i << std::endl;
}

void do_something(int& i)
{
	++i;
}

void b1(){
	for (unsigned j = 0; j < 1000000; ++j)
	{
		std::cout << "b1\n";
	}

}

void test1()
{
	std::thread t(hello1);
	b1();
	t.join();
	//b1();
}

struct func
{
	int& i;
	func(int& i_) :i(i_){}
	void operator()()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			hello2(i);
		}
	}
};


void oops(){
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();
	b1();
	std::cout << my_thread.joinable()<<std::endl;
}

void f1(){
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try{
		hello1();
	}
	catch(...){
		t.join();
		throw;
	}
	std::cout << "out of try-throw\n";
	t.join();

}

class thread_guard{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :t(t_){};

	~thread_guard(){
		if (t.joinable())
		{
			t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;

};

void f2(){
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	b1();

}

void oprn_document_and_dispaly(std::string const& filename){ //todo
}

typedef enum
{
	open_new_document,
	others
} xxx;

bool done_editing(){
	return true;
}

struct user_command{
	std::string a;
	xxx type;

};

user_command get_user_input()
{
	user_command a;
	return a;
}

std::string get_file_name_frome_user(){
	return "xxx";
}

void process_user_input(user_command x){

}

void edit_document(std::string const& filename)
{
	oprn_document_and_dispaly(filename);
	while (!done_editing())
	{
		user_command cmd = get_user_input();
		if (cmd.type == open_new_document)
		{
			std::string const new_name = get_file_name_frome_user();
			std::thread t(edit_document, new_name);
			t.detach();
		}
		else
		{
			process_user_input(cmd);
		}
	}
}

void f3(int i, std::string const& s)
{
	for (int x = 0; x < i; x++)
	{
		std::cout << s.length();
	}
}

void opps2()
{
	char buffer[1024];
	sprintf(buffer, "aaaaaaa\n");
	std::thread t(f3, 3, std::string(buffer));
	t.detach();
}

void updata_data_for_widget(user_command& data){
	data.type = others;
}

void testoops(){
	user_command xxx;
	xxx.type = open_new_document;
	std::thread t(updata_data_for_widget, std::ref(xxx));
	t.join();
	std::cout << xxx.type;

}

class X
{
public:
	X();
	~X();
	void do_lengthy_work(){
		std::cout << "test\n";
	};
private:

};

X::X()
{
}

X::~X()
{
}

X my_x;

void test3(){
	std::thread t(&X::do_lengthy_work, &my_x);
}

class big_object
{
public:
	
	big_object();
	~big_object();
	
private:

};

big_object::big_object()
{
}

big_object::~big_object()
{
}

void process_big_object(std::unique_ptr<big_object>){};

void test4(){
	std::unique_ptr<big_object> p(new big_object);
	
	//std::thread t(process_big_object, std::move(p));//problem
}

void some_function(){
	std::cout << 1;
};
void some_other_function(){
	std::cout << 2;
};

void test5(){

	std::thread t1(some_function);
	std::thread t2 = std::move(t1);
	t1 = std::thread(some_other_function);
	std::thread t3;
	t3 = std::move(t2);
	t1 = std::move(t3);
	//t2 = std::thread(some_other_function);
	//t1.join();
	//t2.join();
	//t3.join();

}

void teststdmove()
{
	std::string aaa = "hello";
	std::vector<std::string> av;
	av.push_back(std::move(aaa));
	std::cout << "str value:" << aaa << std::endl;
	std::cout << "vector v[0]:" << av[0] << std::endl;

}

std::thread f4(){
	void some_function();
	return std::thread(some_function);

}

std::thread g4(){
	void some_others_function();
	std::thread t(some_other_function);
	return t;
}

void test6(){
	std::thread t1 = f4();
	t1.join();
	std::thread t2 = g4();
	t2.join();

}

class scoped_thread
{
public:
	explicit scoped_thread(std::thread t_) :t(std::move(t_)){
		if (!t.joinable())
		{
			throw std::logic_error("No thread");
		}
	}
	~scoped_thread(){
		t.join();
	};

	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;

private:
	std::thread t;
};

void f5(){
	int some_local_state = 0;
	scoped_thread t(std::thread(func(some_local_state)));
	b1();
}

void do_work(unsigned int id){
	std::cout << id << std::endl;
	std::cout << "thread id: "<<std::this_thread::get_id() << std::endl;
}

void f6(){
	std::vector<std::thread> threads;
	for (unsigned int i = 0; i < 20; i++)
	{
		threads.push_back(std::thread(do_work, i));
	}
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

}

template<typename Iterator,typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result){
		result = std::accumulate(first, last, result);
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);
	std::cout << "length: " << length << std::endl;

	if (!length)
		return init;

	unsigned long const min_per_thread = 2;
	unsigned long const max_threads =
		(length + min_per_thread - 1) / min_per_thread;
	std::cout << "max_threads: " << max_threads << std::endl;

	unsigned long const hardware_threads =
		std::thread::hardware_concurrency();
	std::cout << "cpu:" << hardware_threads << std::endl;

	unsigned long const num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	std::cout << "num_threads: " << num_threads << std::endl;

	unsigned long const block_size = length / num_threads;
	std::cout << "block_size: " << block_size << std::endl;

	std::vector<T> results(num_threads);
	std::vector<std::thread>  threads(num_threads - 1);

	Iterator block_start = first;
	std::cout << "num_threads: " << num_threads << std::endl;
	for (unsigned long i = 0; i<(num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		threads[i] = std::thread(
			accumulate_block<Iterator, T>(),
			block_start, block_end, std::ref(results[i]));
		block_start = block_end;
	}
	accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}

void test7(){
	std::vector<int> vi;
	for (int i = 0; i<10; ++i)
	{
		vi.push_back(10);
	}
	int sum = parallel_accumulate(vi.begin(), vi.end(), 5);
	std::cout << "sum=" << sum << std::endl;
}

void main(){
	//test1();
	//oops();
	//f2();
	//opps2();
	//test5();
	//f4();
	//g4();
	//teststdmove();
	//test6();
	//f5();
	//f6();
	//test7();
	//std::thread::id master_thread = std::this_thread::get_id();
	//std::cout << std::this_thread::get_id() << std::endl;
	//std::cout << master_thread << std::endl;
}