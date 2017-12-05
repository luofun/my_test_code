# -*- coding: gbk -*- 
import smtplib  
from email.mime.text import MIMEText  
mailto_list=['627018553@qq.com']         
mail_host="smtp.163.com"            
mail_user="luofunfun"                          
mail_pass="mail2017luofun"                             
mail_postfix="163.com"                     
def send_mail(to_list,sub,content):  
    me="luofunfun"+"<"+mail_user+"@"+mail_postfix+">"  
    msg = MIMEText(content,_subtype='plain')  
    msg['Subject'] = sub  
    msg['From'] = me  
    msg['To'] = ";".join(to_list)                
    try:  
        server = smtplib.SMTP()  
        server.connect(mail_host)                              
        server.login(mail_user,mail_pass)               
        server.sendmail(me, to_list, msg.as_string())  
        server.close()  
        return True  
    except Exception as e:  
        print (str(e))  
        return False
if __name__ == '__main__':
    for i in range(1):                             
        if send_mail(mailto_list,"再发一次代码","代码在XXX"):  
            print ("done!")  
        else:  
            print ("failed!")  
