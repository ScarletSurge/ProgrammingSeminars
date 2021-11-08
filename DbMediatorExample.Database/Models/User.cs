using DbMediatorExample.Database.Models.Enums;

namespace DbMediatorExample.Database.Models
{

    public sealed class User
    {

        public int Id { get; set; }

        public string Login { get; set; }

        public Role Role { get; set; }

        public override string ToString()
        {
            return $"Id = {Id}, Login = {Login}, Role = {Role}";
        }

    }

}