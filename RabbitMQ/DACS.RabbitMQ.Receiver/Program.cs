using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using RabbitMQ.Client;
using RabbitMQ.Client.Events;

namespace DACS.RabbitMQ.Receiver
{
    class Program
    {
        static void Main(string[] args)
        {
            var connectionFactory = new ConnectionFactory
            { 
                HostName = "localhost"
            };

            using var rabbitMQConnection = connectionFactory.CreateConnection();

            using var rabbitMQChannel = rabbitMQConnection.CreateModel();

            const string queueName = "MessageQueueSample";
            
            rabbitMQChannel.QueueDeclare(queueName, false, false, false
                , new Dictionary<string, object>());

            var receiver = new EventingBasicConsumer(rabbitMQChannel);
            receiver.Received += (sender, eventArgs) =>
            {
                var messageData = eventArgs.Body.ToArray();
                var message = Encoding.UTF8.GetString(messageData);

                Console.WriteLine($"Message successfully received: \"{message}\".");
                Task.Delay(50).GetAwaiter().GetResult();
            };
            
            rabbitMQChannel.BasicConsume(queueName, true, receiver);
            while (true) ;
        }
    }
}