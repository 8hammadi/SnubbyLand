from pubnub.callbacks import SubscribeCallback
from pubnub.enums import PNStatusCategory
from pubnub.pnconfiguration import PNConfiguration
from pubnub.pubnub import PubNub
import time
import os
path= "myProgram"
oldmessage="-"
# os.mkfifo(path)
S="S"#input("Chaneel":)
pnconfig = PNConfiguration()

pnconfig.publish_key = 'pub-c-4eeaec72-af1a-4b75-9534-7ed298b15a29'
pnconfig.subscribe_key = 'sub-c-b1fc757e-3d57-11ea-be28-ae0ede4a022d'
pnconfig.ssl = True

pubnub = PubNub(pnconfig)

def my_publish_callback(envelope, status):
	# Check whether request successfully completed or not
	if not status.is_error():
		pass

class MySubscribeCallback(SubscribeCallback):
	global oldmessage
	def presence(self, pubnub, presence):
		pass
	def status(self, pubnub, status):
		pass
	def message(self, pubnub, message):
		# global oldmessage
		print ("from device 1: " + message.message)
		# if oldmessage==message.message:return
		# oldmessage=message.message
		# fifo=open(path,'w')
		# fifo.write(message.message)
		# fifo.close()

pubnub.add_listener(MySubscribeCallback())
pubnub.subscribe().channels(S).execute()

## publish a message
# while(1):
# 	fifo=open('yourProgram','r')
# 	msg=fifo.read()
# 	print(msg)
# 	pubnub.publish().channel(S).message(str(msg)).pn_async(my_publish_callback)
# 	fifo.close()
while True:
	msg = input("Input a message to publish: ")
	if msg == 'exit': os._exit(1)
	pubnub.publish().channel(S).message(str(msg)).pn_async(my_publish_callback)
	
