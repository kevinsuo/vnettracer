#!/usr/bin/python
#

from __future__ import print_function
from bcc import BPF

import sys
import socket
import os
import ConfigParser
import struct
import subprocess



# load BPF program
b1 = BPF(src_file="script.c")


def initDB():
	global db_ip
	global db_port
	global db_name

        dbconfig = ConfigParser.ConfigParser()
        dbconfig.read('config/database.cfg')
        db_ip    = dbconfig.get('Database', 'db_ip')
        db_port  = dbconfig.get('Database', 'db_port')
        db_name  = dbconfig.get('Database', 'db_name')



def initTrace():
	function_1 = b1.load_func("function1", BPF.SOCKET_FILTER)

        ndconfig = ConfigParser.ConfigParser()
        ndconfig.read('config/networkdevice.cfg')
        nd_1 = ndconfig.get('NetworkDevice', 'nd_1')

	BPF.attach_raw_socket(function_1, nd_1)



def genSizeFile(fileName, fileSize):
        #file path
        filePath="./"+fileName+".txt"
        ds=0
        with open(filePath, "wb") as f:
                while (ds<fileSize):
                        f.write(str(" "))
                        f.write("\n")
                        ds=os.path.getsize(filePath)


def execution():
	global db_ip
	global db_port
	global db_name
	global realtime = 1

	genSizeFile("tracedata",10*1024)
	print("%-18s %-18s %-18s %-18s" % ("TIME(s)", "TIME(ns)", "protocol", "packet length"))

	tracenum=30
	offset=0

	# format output
	with open("tracedata.txt", "r+b") as f:
		mm = mmap.mmap(f.fileno(), 0)		

		while (tracenum > 0):
			tracenum=tracenum-1
			(task, pid, cpu, flags, ts, msg) = b1.trace_fields()

			(time, tracepointid, packetlen)= msg.split()
			tracepointid_int = int(tracepointid, 10)

			# send to database in realtime
			if realtime == 1:
				cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest11,hostname=VM1,tracepointID="+tracepointid+" clock="+time+",packetlen=\""+packetlen+"\"'"
				child = subprocess.Popen(cmd, shell=True)
			# save to local file
			else:
				cmd = time+";"+tracepointid+";"+packetlen+"\n"
				mm[offset:len(cmd)] = cmd
				offset = offset + len(cmd) + 2

		mm.seek(0)
		print mm.readline()		
		mm.close()


def main():
 	initDB()
	initTrace()
	execution()


if __name__ == "__main__":
    main()


