using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using RabbitMQ.Client;

namespace DACS.RabbitMQ.Sender
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

            var i = 0;
            while (true)
            {
                var data = $"Data on iteration #{++i}";
                var dataBytes = Encoding.UTF8.GetBytes(data);

                rabbitMQChannel.BasicPublish(string.Empty, queueName, body: dataBytes);
                
                Console.WriteLine($"Message #{i} successfully published.");
                //Thread.Sleep(100); - bad
                Task.Delay(100).GetAwaiter().GetResult();
            }
        }
    }
}