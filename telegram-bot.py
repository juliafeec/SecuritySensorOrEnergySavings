import telegram

project_token = '178932813:AAGsjrWc2u4fWwgUT7WFHEYaIIToBvHdt2k'
bot = telegram.Bot(token=project_token)
print bot
updates = bot.getUpdates()
print "Printing updates"

if updates:
    for update in updates:
        last = update['update_id']
        print update
    last += 1
    bot.getUpdates(offset=last)

