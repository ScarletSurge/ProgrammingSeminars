using System;

namespace DbMediatorExample.Database.Models
{

    public sealed class Log
    {

        public int Id { get; set; }

        public string UserLogin { get; set; }

        public string Description { get; set; }

        public DateTime Created { get; set; }

    }

}