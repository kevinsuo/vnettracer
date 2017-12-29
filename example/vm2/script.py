#!/usr/bin/python


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
	function_fun_1 = b1.load_func("fun1", BPF.SOCKET_FILTER)
	function_fun_2 = b1.load_func("fun2", BPF.SOCKET_FILTER)
	function_fun_3 = b1.load_func("fun3", BPF.SOCKET_FILTER)

        ndconfig = ConfigParser.ConfigParser()
        ndconfig.read('config/networkdevice.cfg')
        nd_1 = ndconfig.get('NetworkDevice', 'nd_1')
        nd_2 = ndconfig.get('NetworkDevice', 'nd_2')
        nd_3 = ndconfig.get('NetworkDevice', 'nd_3')

	BPF.attach_raw_socket(function_fun_1, nd_1)
	BPF.attach_raw_socket(function_fun_2, nd_2)
	BPF.attach_raw_socket(function_fun_3, nd_3)



def execution():
        global db_ip
        global db_port
        global db_name


	print("%-18s %-18s %-18s %-18s" % ("TIME(s)", "TIME(ns)", "tracepointID", "packetID"))


	# format output
	while 1:
		(task, pid, cpu, flags, ts, msg) = b1.trace_fields()

		(time, tracepointid, packetid)= msg.split()
		tracepointid_int = int(tracepointid, 10)


                if tracepointid_int == 14:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest14,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"
                if tracepointid_int == 15:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest15,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"
                if tracepointid_int == 16:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest16,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"


                if tracepointid_int == 21:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest21,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"
                if tracepointid_int == 22:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest22,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"
                if tracepointid_int == 23:
                        cmd = "curl -i -XPOST 'http://" + db_ip + ":" + db_port + "/write?db=" + db_name + "' --data-binary 'timetracetest23,hostname=VM2,tracepointID="+tracepointid+" clock="+time+",packetID=\""+packetid+"\"'"


		child = subprocess.Popen(cmd, shell=True)




def main():
        initDB()
        initTrace()
        execution()


if __name__ == "__main__":
    main()



