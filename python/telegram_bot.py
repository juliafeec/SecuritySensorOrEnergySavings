import telegram

num_pessoas = 0
status_luz = 0
temperatura = 0

project_token = '178932813:AAGsjrWc2u4fWwgUT7WFHEYaIIToBvHdt2k'
bot = telegram.Bot(token=project_token)

def reply(chat_id, msg):
    if msg == "/pessoas":
        bot.sendMessage(chat_id=chat_id, text="Numero de pessoas: " +
                        str(num_pessoas))
    elif msg == "/luz":
        status = "Acesa" if status_luz else "Apagada" 
        bot.sendMessage(chat_id=chat_id, text=status)
    elif msg == "/temperatura":
        bot.sendMessage(chat_id=chat_id, text="Temperatura: " +
                        str(temperatura) + "C")
    elif msg == "/help":
        bot.sendMessage(chat_id=chat_id, text="/pessoas         -- Mostra numero de pessoas no comodo\n" +
                                              "/luz                   -- Mostra se a luz esta acesa ou apagada\n" +
                                              "/temperatura -- Mostra a temperatura em graus Celsius")
    else:
        bot.sendMessage(chat_id=chat_id, text="Comando desconhecido")        

with open("/home/root/arduino_comm", "r") as file:
    while True:
        updates = bot.getUpdates()
        if updates:
            for update in updates:
                reply(update.message.chat_id, update.message.text)
                last = update['update_id']
            last += 1
            bot.getUpdates(offset=last)

        lines = file.readlines()
        for line in lines:
            if line.startswith("luz_on"):
                status_luz = 1
            elif line.startswith("luz_off"):
                status_luz = 0
            elif line.startswith("pessoas_"):
                num_pessoas = int(line.split("_")[1])
            elif line.startswith("temperatura_"):
                temperatura = float(line.split("_")[1])
            else:
                print line
