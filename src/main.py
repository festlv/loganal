import datetime
import pylibftdi
import sys
from io import BytesIO

class Reader():
	def __init__(self, clock_rate, output, read_ms):
		"""
		Opens FTDI device with max possible baud rate. It reads data from device and writes VCD formatted file to output. 
		Reads are performed until read_ms is reached (e.g. read_ms=1000 will read samples for 1 second)
		"""

		
		self.dev = pylibftdi.Device(device_id="AEVUC5TT")
		self.dev.baudrate = 3000000
		self.read_ms = read_ms
		self.clock_rate = clock_rate
		self.out = output
		self.var_identifiers = ('!','@','#','$','%','^','&','*')
		self.run()

	def print_vcd_header(self):
		self.out.write("$date %s $end\n" % (datetime.datetime.now().strftime("%b %d %Y %H:%M:%s")))
		self.out.write("$version Loganal v0.1 $end\n")
		self.out.write("$timescale 1 us $end\n")
		for (ident, num) in zip(self.var_identifiers, range(0,8)):
			pass
			#self.out.write("$var wire 1 %s ch%d $end\n" % (ident, num))
		self.out.write("$var wire 8 ! ch[0:7]\n")
		self.out.write("$enddefinitions $end\n")
		self.out.write("$dumpvars\n")

	def run(self):
		self.print_vcd_header()
		num_samples = self.read_ms * self.clock_rate / 1000
		read_samples = 0
		while read_samples <= num_samples:
			tmp = self.dev.read(1024)
			for t in tmp:
				self.out.write("#%d\n" % read_samples)
				self.out.write("b%s !\n" % bin(ord(t))[2:].zfill(8))
				#for (ident, bit) in zip(self.var_identifiers, range(0,8)):
				#		self.out.write("%d%s\n" % (int(ord(t)&(1<<bit)>0), ident))
				read_samples+=1

if __name__=='__main__':
	cs = BytesIO()
	print(datetime.datetime.now())
	r = Reader(1000000,cs, 1000)
	print(datetime.datetime.now())
	#print cs.getvalue()


