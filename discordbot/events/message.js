const name = 'message';
function execute(message) {
  console.log(
    `${message.author.tag} in #${message.channel.name} sent: ${message.content}`
  );
}

export { name, execute };
