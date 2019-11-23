#-*-coding:utf-8-*-

import sys
import smtplib
from email.mime.text import MIMEText
from email.header import Header
import json
import os

f=open('./mail_config.json')
content = f.read()
dic = json.loads(content)
mail_host = dic['mail_host']
mail_user = dic['mail_user']
mail_pass = dic['mail_pass']


sender = dic['sender']
receivers = []
receivers.append(sys.argv[2])

message = MIMEText('验证码:'+ sys.argv[1], 'plain', 'utf-8')
message['From'] = 'IM <' + sender + '>'
message['To'] = 'Users <' + receivers[0] + '>'

subject = 'IM验证码测试'
message['Subject'] = Header(subject,'utf-8')

try:
    smtpObj = smtplib.SMTP_SSL(mail_host,465)
    smtpObj.login(mail_user,mail_pass)
    smtpObj.sendmail(sender,receivers,message.as_string())
    print("send success")
except smtplib.SMTPException:
    print("send fialed")
