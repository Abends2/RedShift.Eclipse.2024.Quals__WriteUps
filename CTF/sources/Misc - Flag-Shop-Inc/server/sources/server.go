package main

import (
   "fmt"
   "net"
   "strconv"
   "strings"
   "io/ioutil"
   "log"
)

func main() {
   listener, _ := net.Listen("tcp", "0.0.0.0:13338") // открываем слушающий сокет
   for {
		conn, err := listener.Accept() // принимаем TCP-соединение от клиента и создаем новый сокет
      	if err != nil {
         	log.Fatal(err)
      	}
      	go handleClient(conn) // обрабатываем запросы клиента в отдельной го-рутине
   	}
}

func handleClient(conn net.Conn) {
   defer conn.Close() // закрываем сокет при выходе из функции

   buf := make([]byte, 1024) // буфер для чтения клиентских данных

	account_balance := 1100

	conn.Write([]byte(`
         ______ _                _____ _                 _ 
        |  ____| |              / ____| |               | |
        | |__  | | __ _  __ _  | (___ | |__   ___  _ __ | |
        |  __| | |/ _' |/ _' |  \___ \| '_ \ / _ \| '_ \| |
        | |    | | (_| | (_| |  ____) | | | | (_) | |_) |_|
        |_|    |_|\__,_|\__, | |_____/|_| |_|\___/| .__/(_)
                         __/ |                    | |      
                        |___/                     |_|      
						`))

	conn.Write([]byte("\nWelcome to our shop!"))

   for {
		conn.Write([]byte("\n=================\n"))
      	conn.Write([]byte("\n1. Check your balance\n2. Buy a flag\n\nWhat do you want?\n")) // пишем в сокет
		conn.Write([]byte("\n=================\n"))

      menu, err := conn.Read(buf) // читаем из сокета
      if err != nil {
         fmt.Println(err)
         break
      }

		if strings.TrimRight(string(buf[:menu]), "\n") == "1" {
			conn.Write([]byte("\nYour balance: " + strconv.Itoa(account_balance) + "\n")) // пишем в сокет

		} else if strings.TrimRight(string(buf[:menu]), "\n") == "2" {
			conn.Write([]byte("\nOur products\n1. Pirate flag\n2. EclipseCTF{...}\n\nWhat do you want to buy?\n")) // пишем в сокет
			flag_menu, err := conn.Read(buf)
			if err != nil {
				fmt.Println(err)
				break
			}

			if strings.TrimRight(string(buf[:flag_menu]), "\n") == "1" {
				conn.Write([]byte("\nThe cost of this flag is 900$, enter a count of flags that you want to buy:\n")) // пишем в сокет
				
				number_flags, err := conn.Read(buf) 
				if err != nil {
					fmt.Println(err)
					break
				}

				cost, _ := strconv.Atoi(strings.TrimRight(string(buf[:number_flags]), "\n"))

				total_cost := 900 * cost 

				conn.Write([]byte("\nTotal cost: " + strconv.Itoa(total_cost) + "$\n"))
				
				if total_cost <= account_balance {
					account_balance = account_balance - total_cost
					conn.Write([]byte("\nYour balance after buying chosen flags: " + strconv.Itoa(account_balance) + "$\n"))
				} else {
					conn.Write([]byte("\nYou don't have enough money!\n"))
				}
			} else if strings.TrimRight(string(buf[:flag_menu]), "\n") == "2" {
				conn.Write([]byte("\nThe cost of this flag is: 10 000$!\nAnd we have only 1 flag! (Enter 1 for buying)\n"))
				
				real_count_of_flags, err := conn.Read(buf)
				if err != nil {
					fmt.Println(err)
					break
				}

				if strings.TrimRight(string(buf[:real_count_of_flags]), "\n") == "1" {
					if account_balance >= 10000 {
						file_data, err := ioutil.ReadFile("/app/sources/flag.txt")
						if err != nil {
							fmt.Println(err)
							break
						}
						conn.Write([]byte("Congratulations! " + string(file_data) + "\nSee you later!\n"))
						break
					} else {
						conn.Write([]byte("\nYou don't have enough money!\n"))
					}
				} else {
					conn.Write([]byte("\nNot a valid value! Exit...\n"))
					break
				}
			} else {
				conn.Write([]byte("\nNot a valid value! Exit...\n"))
				break
			}
		} else {
			conn.Write([]byte("\nNot a valid value! Exit...\n"))
			break
		}
   }
}
