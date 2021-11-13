namespace DbDemo.Models
{
    
    public sealed class EmployeeFullInfo
    {

        public int Id { get; }
        
        public string Name { get; }

        public decimal Salary { get; }

        public string RoleName { get; }

        public string RoleDescription { get; }

        public EmployeeFullInfo(int id, string name, decimal salary,
            string roleName, string roleDescription)
        {
            Id = id;
            Name = name;
            Salary = salary;
            RoleName = roleName;
            RoleDescription = roleDescription;
        }

    }
    
}