namespace DbDemo.Models
{
    
    internal sealed class EmployeeFullInfo
    {

        public int Id { get; private set; }
        
        public string Name { get; private set; }

        public decimal Salary { get; private set; }

        public string RoleName { get; private set; }

        public string RoleDescription { get; private set; }

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