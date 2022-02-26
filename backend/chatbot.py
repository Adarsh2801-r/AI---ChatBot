#from crypt import methods
import aiml
import os
from flask import Flask,request,jsonify
from flask_cors import CORS,cross_origin;

app = Flask(__name__)
CORS(app,resources={r"*":{"origins":"*"}})
app.config['CORS HEADERS'] = 'Content-Type'
print("hello")
kernel = aiml.Kernel()
folder = "C:/Users/BITS-PC/chatbot/backend/aiml-en-us-foundation-alice"
for file in os.listdir(folder):
    kernel.learn(os.path.join(folder,file))

kernel.learn("basic_chat.aiml")
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
    print("DATA=====>",str(data))
    return str(kernel.respond(data))

  
if __name__ == '__main__':
    app.run()