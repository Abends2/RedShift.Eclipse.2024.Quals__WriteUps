import socketserver
import time
import math

from module import generate_math_expression


ascii_draw = """
  __  __         _   _       ___  _ 
 |  \/  |  ____ | | | |     |__ \| |
 | \  / | / __ \| |_| |__      ) | |
 | |\/| |/ / _` | __| '_ \    / /| |
 | |  | | | (_| | |_| | | |  |_| |_|
 |_|  |_|\ \__,_|\__|_| |_|  (_) (_)
          \____/                    

I am sooo tired, I have solved only 5 exercises, but I need 1000...
It would be nice to automate the process so that I can go for a walk faster
Plz, help me :/\n
"""

class MyTCPHandler(socketserver.BaseRequestHandler):
	"""
	The RequestHandler class for our server.
	
	It is instantiated once per connection to the server, and must
	override the handle() method to implement communication to the
	client.
	"""

	def handle(self):
		# Выводим ASCII-баннер
		self.request.sendall(ascii_draw.encode())

		for i in range(0, 100):
			math_expression = generate_math_expression()
			result = eval(math_expression)

			self.request.sendall("# ".encode() + str(i).encode() + " | 100: Solve this: ".encode() + math_expression.encode() + " = ".encode())

			answer = self.request.recv(1024).strip()
			if i == 99:
				self.request.sendall("EclipseCTF{I_h4t3_wh3n_my_m0m_t3ll5_m3_g0_sl3pp1n6}\n".encode())
				return 0
			if int(answer) == result:
				continue
			else:
				return 0
								

if __name__ == "__main__":
	HOST, PORT = "0.0.0.0", 36363

	# Create the server, binding to localhost on port N
	server = socketserver.TCPServer((HOST, PORT), MyTCPHandler)

	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
	server.serve_forever()
