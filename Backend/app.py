import sacn


# provide an IP-Address to bind to if you want to send multicast packets from a specific interface
receiver = sacn.sACNreceiver()
receiver.start()  # start the receiving thread


@receiver.listen_on('universe', universe=1)  # listens on universe 1
def callback(packet):  # packet type: sacn.DataPacket
    for i in range(0, len(packet.dmxData), 4):
        if packet.dmxStartCode == 0:
            print('channel: ', (i - (3 * i // 4)) + 1,)
            parse = packet.dmxData[i:i+4]
            print('red:', parse[0], ' green: ', parse[1], ' blue: ', parse[2], ' white: ', parse[3])



receiver.join_multicast(1)
