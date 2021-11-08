namespace ThirdCourse.WPF.Strings.Models
{

    public sealed class StringsModel
    {

        public StringsModel()
        {
            FirstString = SecondString = "123";
        }

        public string FirstString
        {
            get;

            set;
        }

        public string SecondString
        {
            get;

            set;
        }

        public bool IsLeftStringVisible
        {
            get;

            set;
        }

    }

}