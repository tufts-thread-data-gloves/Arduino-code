import asyncio
import struct
from bleak import discover
from bleak import BleakClient
from bleak.uuids import uuid16_dict
from bleak.uuids import uuid128_dict
import matplotlib.pyplot as plt



async def run():
    done = False
    while(not done):
        print("finding device")
        devices = await discover()
        for d in devices:
            if d.address == "E8:C8:3B:DA:9C:83":
                done = True
    client = BleakClient("E8:C8:3B:DA:9C:83", loop)
    if (await client.connect()):
        services = await client.get_services()
        print(services.characteristics)
        plt.ion()
        time = []
        # index = []
        middle = []
        ctr = 0
        while(1):
            # print("Gyroscope")
            # print(struct.unpack('cccc', await client.read_gatt_char("1b9b0002-3e7e-4c78-93b3-0f86540298f1")))
            # print("Accelerometer")
            # print(struct.unpack('cccc', await client.read_gatt_char("1b9b0001-3e7e-4c78-93b3-0f86540298f1")))
            ctr += 1
            if (ctr <= 25):
                # index.append(struct.unpack('h', await client.read_gatt_char("1b9b0002-3e7e-4c78-93b3-0f86540298f1"))[0]*(128/1024))
                middle.append(struct.unpack('h', await client.read_gatt_char("1b9b0001-3e7e-4c78-93b3-0f86540298f1"))[0]*(128/1024))
                time = range(ctr)
            else:
                middle.pop(0)
                # index.pop(0)
                middle.append(struct.unpack('h', await client.read_gatt_char("1b9b0001-3e7e-4c78-93b3-0f86540298f1"))[0]*(128/1024))
                # index.append(struct.unpack('h', await client.read_gatt_char("1b9b0002-3e7e-4c78-93b3-0f86540298f1"))[0]*(128/1024))
                time = range(ctr-25, ctr)
                plt.xlim(time[0], time[24])
            plt.plot(time, middle, 'r-')
            plt.title("Finger Strain")
            plt.draw()
            plt.pause(0.001)


        # while(1):
        #     print(struct.unpack('ffffff', await client.read_gatt_char("1b9b0001-3e7e-4c78-93b3-0f86540298f1")))

loop = asyncio.get_event_loop()
loop.run_until_complete(run())
