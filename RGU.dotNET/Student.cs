namespace RGU.dotNET;

public class Student
{
    // const
    private readonly string _name;
    private readonly string _surname;
    private readonly string _group;
    private readonly int _course;

    public Student(
        string name,
        string surname,
        string group,
        int course)
    {
        _name = name;
        _surname = surname;
        _group = group;
        _course = course;
    }

    public override string ToString()
    {
        return $"Name: {_name}, Surname: {_surname}, Group: {_group}, Course: {_course}";
    }
}