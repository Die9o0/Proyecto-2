# Import standard python modules.
import sys
import time
import serial
# This example uses the MQTTClient instead of the REST client
from Adafruit_IO import MQTTClient
from Adafruit_IO import Client, Feed
# holds the count for the feed
run_count = 0
# Set to your Adafruit IO username and key.
# Remember, your key is a secret,
# so make sure not to publish it when you publish this code!
ADAFRUIT_IO_USERNAME = "Die9o06"
ADAFRUIT_IO_KEY = "aio_zmbV43itnfxmFZs3ggyuUoogCyb9"
# Set to the ID of the feed to subscribe to for updates.
FEED_ID_receive_1 = 'brazo-tx'
FEED_ID_Send_1 = 'brazo-rx'
FEED_ID_receive_2 = 'antebrazo-tx'
FEED_ID_Send_2 = 'antebrazo-rx'
FEED_ID_receive_3 = 'rueda-izquierda-tx'
FEED_ID_Send_3 = 'rueda-izquierda-rx'
FEED_ID_receive_4 = 'rueda-derecha-tx'
FEED_ID_Send_4 = 'rueda-derecha-rx'
FEED_ID_receive_5 = 'general-tx'
FEED_ID_Send_5 = 'direccion-rx'
# Define "callback" functions which will be called when certain events
# happen (connected, disconnected, message arrived).
def connected(client):
    """Connected function will be called when the client is connected to
    Adafruit IO.This is a good place to subscribe to feed changes. The client
    parameter passed to this function is the Adafruit IO MQTT client so you
    can make calls against it easily.
    """
    # Subscribe to changes on a feed named Counter.
    print('Subscribing to Feed {0}'.format(FEED_ID_receive_1))
    client.subscribe(FEED_ID_receive_1)
    print('Waiting for feed data brazo...')
    print('Subscribing to Feed {0}'.format(FEED_ID_receive_2))
    client.subscribe(FEED_ID_receive_2)
    print('Waiting for feed data antebrazo...')
    print('Subscribing to Feed {0}'.format(FEED_ID_receive_3))
    client.subscribe(FEED_ID_receive_3)
    print('Waiting for feed data rueda izquierda...')
    print('Subscribing to Feed {0}'.format(FEED_ID_receive_4))
    client.subscribe(FEED_ID_receive_4)
    print('Waiting for feed data rueda derecha...')
    print('Subscribing to Feed {0}'.format(FEED_ID_receive_5))
    client.subscribe(FEED_ID_receive_5)
    print('Waiting for feed data direccion...')
def disconnected(client):
    """Disconnected function will be called when the client disconnects."""
    sys.exit(1)
def message(client, feed_id, payload):
    """Message function will be called when a subscribed feed has a new value.
    The feed_id parameter identifies the feed, and the payload parameter has
    the new value.
    """
    print('Feed {0} received new value: {1}'.format(feed_id, payload))

    if feed_id == FEED_ID_receive_1:
        client.publish(FEED_ID_Send_1, payload)
        myArduino.write(bytes([1, int(payload)]))

    elif feed_id == FEED_ID_receive_2:
        client.publish(FEED_ID_Send_2, payload)
        myArduino.write(bytes([2, int(payload)]))

    elif feed_id == FEED_ID_receive_3:
        client.publish(FEED_ID_Send_3, payload)
        myArduino.write(bytes([3, int(payload)]))

    elif feed_id == FEED_ID_receive_4:
        client.publish(FEED_ID_Send_4, payload)
        myArduino.write(bytes([4, int(payload)]))

    elif feed_id == FEED_ID_receive_5:
        myArduino.write(bytes([5, int(payload)]))
        client.publish(FEED_ID_Send_5, payload)
# Create an MQTT client instance.
client = MQTTClient(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
myArduino = serial.Serial(port='COM10', baudrate=2400, timeout=0.1)
# Setup the callback functions defined above.
client.on_connect = connected
client.on_disconnect = disconnected
client.on_message = message
# Connect to the Adafruit IO server.
client.connect()
# The first option is to run a thread in the background so you can continue
# doing things in your program.
client.loop_background()
while True:
    """
    # Uncomment the next 3 lines if you want to constantly send data
    # Adafruit IO is rate-limited for publishing
    # so we'll need a delay for calls to aio.send_data()
    run_count += 1
    print('sending count: ', run_count)
    client.publish(FEED_ID_Send, run_count)
    """
    print('Running "main loop" ')
    time.sleep(3)
