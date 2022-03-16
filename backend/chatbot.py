#from crypt import methods
import aiml
import os
from flask import Flask,request,jsonify
from flask_cors import CORS,cross_origin;
import requests
from bs4 import BeautifulSoup

app = Flask(__name__)
CORS(app,resources={r"*":{"origins":"*"}})
app.config['CORS HEADERS'] = 'Content-Type'
print("hello")
kernel = aiml.Kernel()
folder = "C:/Users/BITS-PC/chatbot/backend/aiml-en-us-foundation-alice"
for file in os.listdir(folder):
    kernel.learn(os.path.join(folder,file))

kernel.learn("C:/Users/BITS-PC/chatbot/backend/basic_chat.aiml")
'''while True:
    print(kernel.respond(input("Enter msg >> ")))'''




@app.route('/')
@cross_origin(origin='*')
def hello_world():
    return 'Hello World'

@app.route('/user',methods=['POST'])
@cross_origin(origin='*')
def user():
    jsony = request.json
    data=jsony['msg']
    #print("DATA=====>",str(data))
    if(("weather" in data) and ("city" in data)):
        resp = ""
        city = data.split(" ")[-2]
        url = "https://www.google.com/search?q="+"weather"+city
 
        # requests instance
        html = requests.get(url).content
 
        # getting raw data
        soup = BeautifulSoup(html, 'html.parser')
        # get the temperature
        temp = soup.find('div', attrs={'class': 'BNeawe iBp4i AP7Wnd'}).text
 
        # this contains time and sky description
        strs = soup.find('div', attrs={'class': 'BNeawe tAd8D AP7Wnd'}).text
 
        # format the data
        dat = strs.split('\n')
        time = dat[0]
        sky = dat[1]
        # list having all div tags having particular clas sname
        listdiv = soup.findAll('div', attrs={'class': 'BNeawe s3v9rd AP7Wnd'})
 
        # particular list with required data
        strd = listdiv[5].text
 
        # formatting the string
        pos = strd.find('Wind')
        other_data = strd[pos:]
        resp += ("City: "+city+" , "+"Temperature is: " + temp + " , " + "Time: " + time + " , " + "Sky Description: " + sky) 
        return str(resp)
    
    return str(kernel.respond(data))



  
if __name__ == '__main__':
    app.run()
