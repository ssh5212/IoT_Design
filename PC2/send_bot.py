import telegram

def bot_send(text):
    token = "5045771515:AAGxYSPcVDuSRxpumo-LJz-vGAtNd9W8d1c"
    bot = telegram.Bot(token=token)
    my_id = "1145764577"

    bot.sendMessage(chat_id=my_id, text=text)

with open("retrench.txt", "w") as f:
    retrench = f.read()

bot_send(f"외출시간 동안 {retrench}kWh 만큼의 전력을 절약했습니다!!")