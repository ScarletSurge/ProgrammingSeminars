using System;

namespace RGU.DataBases.ClientApplication.Launcher.App;

public class Student
{
    
    public string RecordBookNumber { get; set; }
    
    public string? Surname { get; set; }
    
    public string? Name { get; set; }
    
    public string? Patronymic { get; set; }

    public DateTime Birthday { get; set; }

    public int? Course { get; set; }

    public string? Faq { get; set; }

    public int? ScientificAdviserId { get; set; }

}