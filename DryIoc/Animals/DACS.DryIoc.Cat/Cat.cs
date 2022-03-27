using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Cat
{

    public sealed class Cat : IAnimal
    {

        public Cat()
        {
            //var x = 5;
        }

        public int LegsCount =>
            4;

        public string Voice() =>
            "Meow";

    }
    
}