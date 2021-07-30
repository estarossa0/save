import { Client } from 'discord.js';
import { WebhookClient } from 'discord.js';
import * as Discord from 'discord.js';
import jsonFile from 'jsonfile';
import fetch from 'node-fetch';

const client = new Client();
const { prefix, token } = jsonFile.readFileSync('./config.json');

client.once('ready', async () => {
  fetch('https://jsonplaceholder.typicode.com/photos/2')
    .then((res) =>
      res.json().then((res) => {
        console.log(res);
        client.channels.cache.forEach((value) => {
          if (value.name == 'test') value.send(res.thumbnailUrl);
        });
      })
    )
    .catch((err) => console.log(err));
});

client.login(token);
