namespace DbMediatorExample.Database.Models
{

    public class Region
    {

        public int Id { get; set; }

        public string Name { get; set; }

        public override string ToString()
        {
            return $"Id = {Id}, Name = \"{Name}\"";
        }

    }

}