using DACS.DryIoc.Domain;

namespace DACS.DryIoc.Dog
{
    
    public sealed class Dog : IAnimal
    {

        public int LegsCount =>
            4;

        public string Voice() =>
            "Woof";

    }
    
}