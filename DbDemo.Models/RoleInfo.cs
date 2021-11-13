namespace DbDemo.Models
{
    
    public sealed class RoleInfo
    {

        public int Id { get; }

        public string Name { get; }

        public string Description { get; }

        public RoleInfo(int id, string name, string description)
        {
            Id = id;
            Name = name;
            Description = description;
        }
        
    }
    
}