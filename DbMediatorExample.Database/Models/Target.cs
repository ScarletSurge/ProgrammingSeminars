using System;

namespace DbMediatorExample.Database.Models
{

    public class Target
    {

        public int Id { get; set; }

        public string Login { get; set; }

        public string Name { get; set; }

        public string Surname { get; set; }

        public DateTime BirthDate { get; set; }

        public string Region { get; set; }

        public override string ToString()
        {
            return $"Id = {Id}, Login = \"{Login}\", Name = \"{Name}\", Surname = \"{Surname}\"," +
                $"BirthDate = {BirthDate:dd/mm/yyyy}, Region = \"{Region}\"";
        }

    }

}