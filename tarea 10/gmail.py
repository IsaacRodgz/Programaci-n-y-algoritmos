# -*- coding: utf-8 -*-

# ID: 132715652489-hnh3v1cupc6vvd739lpiq350knkvs9rc.apps.googleusercontent.com
# secreto: dBWAJDlsKEf0gGiTBx-Tgw5a

from googleapiclient.discovery import build
from httplib2 import Http
from oauth2client import file, client, tools
import unidecode

SCOPES = 'https://www.googleapis.com/auth/gmail.readonly'

def strip_accents(text):

    try:
        text = unicode(text, 'utf-8')
    except NameError: # unicode is a default on python 3
        pass

    text = unicodedata.normalize('NFD', text)\
           .encode('ascii', 'ignore')\
           .decode("utf-8")

    return str(text)

def main():

    store = file.Storage('token.json')
    creds = store.get()
    if not creds or creds.invalid:
        flow = client.flow_from_clientsecrets('creds.json', SCOPES)
        creds = tools.run_flow(flow, store)
    service = build('gmail', 'v1', http=creds.authorize(Http()))

    # Call the Gmail API to fetch INBOX
    results = service.users().messages().list(userId='me',labelIds = ['INBOX']).execute()
    messages = results.get('messages', [])

    if not messages:
        print("No messages found.")
    else:
        with open('email_dataset_clean.txt', 'a') as email_file:
            for message in messages:
                msg = service.users().messages().get(userId='me', id=message['id'], format='full').execute()
                line = msg["snippet"]+"\n"
                line_filtered = ' '.join(x.lower() for x in unidecode.unidecode(line).split() if x.isalpha())
                email_file.write(line_filtered+"\n")

if __name__ == '__main__':
    main()
