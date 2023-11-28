//// See https://aka.ms/new-console-template for more information
//
//// CLS
//
//// Эндрю Троельсен "C# 7.0 и платформы .NET и .NET Core"
//// читаем вплоть до делегатов и событий, анонимных делегатов и лямбда-выражений включительно!!1!1
//
//// для экстремалов: Джеффри Рихтер "CLR via C#" издание 4 (розовая обложка)
//
//// Скит "C# для профессионалов"
//
//using RGU.dotNET;
//
//Console.WriteLine("Hello, World!");
//
//int value; // System.Int32
//uint value1;
//
//// value-types (default placed at stack): int, uint, short, ushort, char, byte, sbyte, long, ulong, bool, float, double, decimal, enum, struct, record
//// reference-types (default (always) placed heap): interface, class, string, containers (collections: arrays, lists, hashtables (hashset), dictionary, trees, self-balanced trees, heaps), delegate, record
//
//10.ToString();
//char symbol = 'c';
//string str = "123456";
//
//Student student1 = new Student("Иванов", "Иван", "113", 1);
//var student2 = new Student("Петров", "Пётр", "311", 3);
//
//Console.WriteLine("The value 99999 in various formats:");
//Console.WriteLine("c format: {0:c}", 99999);
//Console.WriteLine("d9 format: {0:d9}", 99999);
//Console.WriteLine("f3 format: {0:f3}", 99999);
//Console.WriteLine("n format: {0:n}", 99999);
//// Обратите внимание, что использование для символа шестнадцатеричного формата
//// верхнего или нижнего регистра определяет регистр отображаемых символов.
//Console.WriteLine ( "Е format: {0:Е}", 99999);
//Console.WriteLine ("е format: {0:е}", 99999);
//Console.WriteLine("X format: {0:X}", 99999);
//Console.WriteLine("x format: {0:x}", 99999);
//
//
//Console.WriteLine(student1);
//Console.WriteLine(student2);
//

using System.Numerics;
using RGU.dotNET;

// class struct record interface

public interface IPrimalityTest
{
    enum PrimalityTestResult
    {
        Prime,
        Composite,
        NotPrimeNorComposite
    }
    
    PrimalityTestResult Check(
        BigInteger value,
        double minimalPrimalityProbability);
}

public class BigIntegerAdditions
{
    public static BigInteger Sqrt(BigInteger n)
    {
        if (n == 0) return 0;
        if (n > 0)
        {
            int bitLength = Convert.ToInt32(Math.Ceiling(BigInteger.Log(n, 2)));
            BigInteger root = BigInteger.One << (bitLength / 2);
            while (!IsSqrt(n, root))
            {
                root += n / root;
                root /= 2;
            }
            return root;
        }
        throw new ArithmeticException("NaN");
    }
    
    private static Boolean IsSqrt(BigInteger n, BigInteger root)
    {
        BigInteger lowerBound = root*root;
        BigInteger upperBound = (root + 1)*(root + 1);
        return (n >= lowerBound && n < upperBound);
    }
}

public sealed class DeterminedPrimalityTest : IPrimalityTest
{
    public IPrimalityTest.PrimalityTestResult Check(
        BigInteger value,
        double minimalPrimalityProbability)
    {
        if (value <= BigInteger.Zero)
        {
            throw new ArgumentException("Value can't be lower or equal to 0", nameof(value));
        }

        if (value == BigInteger.One)
        {
            return IPrimalityTest.PrimalityTestResult.NotPrimeNorComposite;
        }

        if (value == 2)
        {
            return IPrimalityTest.PrimalityTestResult.Prime;
        }

        var valueSqrt = BigIntegerAdditions.Sqrt(value);

        for (BigInteger maybeDivider = 3; maybeDivider <= valueSqrt; maybeDivider += 2)
        {
            if (value % maybeDivider == 0)
            {
                return IPrimalityTest.PrimalityTestResult.Composite;
            }
        }

        return IPrimalityTest.PrimalityTestResult.Prime;
    }
}

public abstract class BasicPrimalityTest : IPrimalityTest
{
    
    public int GetIterationsCount(
        double epsilon)
    {
        // TODO: there are some errors...
        if (epsilon < 0 || epsilon >= 1)
        {
            throw new ArgumentException("Invalid epsilon value", nameof(epsilon));
        }
        
        var iterationsCount = 0;
        double accumulator = 1;
        do
        {
            iterationsCount++;
            accumulator *= OneIterationCompositanceProbability;
        } while (accumulator >= 1 - epsilon);

        return iterationsCount;
    }

    public IPrimalityTest.PrimalityTestResult Check(
        BigInteger value,
        double minimalPrimalityProbability)
    {
        // TODO: value is <= 0
        // TODO: value == 1
        // TODO: value == 2
        // TODO: value % 2 == 0
        
        var iterationsCount = GetIterationsCount(minimalPrimalityProbability);
        for (var i = 0; i < iterationsCount; i++)
        {
            // TODO: generate a
            // TODO: different a
            if (!TestIteration(value, a))
            {
                return IPrimalityTest.PrimalityTestResult.Composite;
            }
        }

        return IPrimalityTest.PrimalityTestResult.Prime;
    }

    protected abstract double OneIterationCompositanceProbability
    {
        get;
    }

    protected abstract bool TestIteration(
        BigInteger primeCandidate,
        BigInteger iterationParameter);
}

public sealed class FermatPrimalityTest : BasicPrimalityTest
{
    protected override double OneIterationCompositanceProbability =>
        0.5;
    
    
}

public sealed class SolovayStrassenPrimalityTest : BasicPrimalityTest
{
    protected override double OneIterationCompositanceProbability =>
        0.5;
    
    
}

public sealed class MillerRabinPrimalityTest : BasicPrimalityTest
{
    protected override double OneIterationCompositanceProbability =>
        0.25;
    
    
}

class Program
{
    static void Foo(IPrimalityTest test)
    {
        try
        {
            switch (test.Check(BigInteger.Zero, 0.9995))
            {
                case IPrimalityTest.PrimalityTestResult.Prime:
                    Console.WriteLine("Value is prime");
                    break;
                case IPrimalityTest.PrimalityTestResult.Composite:
                    Console.WriteLine("Value is composite");
                    break;
                case IPrimalityTest.PrimalityTestResult.NotPrimeNorComposite:
                    Console.WriteLine("Value is not prime nor composite");
                    break;
            }
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine("Invalid value passed!");
        }
    }

    static void Main(string[] args)
    {
        var test = new DeterminedPrimalityTest();
        
        Foo(test);
        Foo(new FermatPrimalityTest());
        var eps = 0.99995;
        var FermatTest = new FermatPrimalityTest();
        var iterationsCount = FermatTest.GetIterationsCount(eps);
        Console.WriteLine($"Iterations count for eps = {eps}: {iterationsCount}");

        Car car1 = new Car();
        car1.Drive();
        Car car2 = new Car("123456", "6", "7", "8", "9", "0");
        car2.Drive();
        car1.Baranka = "1234";
        Console.WriteLine(car1.Baranka);
        Console.WriteLine(car2.Baranka);
        car2.Baranka = "4321";
        Console.WriteLine(car1.Baranka);
        Console.WriteLine(car2.Baranka);
        Console.WriteLine(object.ReferenceEquals(car1, car2));
        Drivable.SomeStaticFunction();
        
        
        var car = car1 + car2;
        Console.WriteLine(car);
        
        try
        {
            var results = Kardano(4, 11, -3, -2, 1e-7);
            Console.WriteLine("Solutions: {0}, {1}, {2}", results[0], results[1], results[2]);
            
        }
        catch (ArgumentNullException ex)
        {
            // 
        }
        catch (ArgumentException ex)
        {
            Console.WriteLine(ex.Message);
            throw new AggregateException(ex);
        }
        finally
        {
            // if (sr != null)
            // {
            //     sr.Dispose();
            // }
            // 
            // sr.Dispose();
        }
        
        Console.WriteLine("I'm alive!");
    }

    static Complex[] Root(
        Complex value,
        int degree)
    {
        var result = new Complex[degree];
        var magnitude = value.Magnitude;
        var magnitudeRoot = Math.Pow(magnitude, 1.0 / degree);
        var argument = value.Phase;
        
        for (var k = 0; k < degree; k++)
        {
            result[k] = new Complex(magnitudeRoot * Math.Cos((argument + 2 * Math.PI * k) / degree), magnitudeRoot * Math.Sin((argument + 2 * Math.PI * k) / degree));
        }

        return result;
    }
    
    // System.Array<double>
    static Complex[] Kardano(double x3Coeff, double x2Coeff, double x1Coeff, double x0Coeff, double epsilon)
    {
        if (epsilon <= 0)
        {
            throw new ArgumentException("Epsilon can't be LT or EQ to 0.", nameof(epsilon));
        }

        if (Math.Abs(x3Coeff) < epsilon)
        {
            throw new ArgumentException("Coefficient at x^3 can't be EQ to 0.", nameof(x3Coeff));
        }

        var p = (3 * x3Coeff * x1Coeff - x2Coeff * x2Coeff) / (3 * x3Coeff * x3Coeff);
        var q = (2 * Math.Pow(x2Coeff, 3) - 9 * x3Coeff * x2Coeff * x1Coeff + 27 * Math.Pow(x3Coeff, 2) * x0Coeff) / (27 * Math.Pow(x3Coeff, 3));

        var Q = Math.Pow(p / 3, 3) + Math.Pow(q / 2, 2);

        // Q == 0
        if (Math.Abs(Q) < epsilon)
        {
            var alpha = Math.Pow(-q / 2, 1.0 / 3);
            var beta = alpha;
            var root1 = alpha + beta;
            var root2 = -root1 / 2;
            return new [] { new Complex(root1, 0), new Complex(root2, 0), new Complex(root2, 0) };
        }
        // Q > 0
        else if (Q > epsilon)
        {
            var sqrtQ = Math.Sqrt(Q);
            var alpha = Math.Cbrt(-q / 2 + sqrtQ);
            var beta = Math.Cbrt(-q / 2 - sqrtQ);
            var root1 = alpha + beta;
            var root23RealPart = root1 / -2;
            var root23ImaginaryPart = (alpha - beta) * Math.Sqrt(3) / 2;
            
            return new []
            {
                new Complex(root1, 0), new Complex(root23RealPart, root23ImaginaryPart), new Complex(
                    root23RealPart, -root23ImaginaryPart)
            };
        }
        else
        {
            var root1 = new Complex(-q / 2, Math.Sqrt(Math.Abs(Q)));
            var root2 = new Complex(-q / 2, -Math.Sqrt(Math.Abs(Q)));

            var roots1 = Root(root1, 3);
            var roots2 = Root(root2, 3);

            for (int i = 0; i < 3; i++)
            {
                var alpha = roots1[i];
                
                // Complex beta;
                var beta = default(Complex);

                for (int j = 0; j < 3; j++)
                {
                    var multiplication = alpha * roots2[j];
                    if (Math.Abs(multiplication.Imaginary) < epsilon && Math.Abs(multiplication.Real + p / 3) < epsilon)
                    {
                        beta = roots2[j];
                        break;
                    }
                }

                if (beta == default(Complex))
                {
                    continue;
                }

                var resultRoot1 = alpha + beta;

                var resultLeftPart = (alpha + beta) / -2;
                var resultRightPart = (alpha - beta) / 2 * Math.Sqrt(3) * new Complex(0, 1);

                return new[] { resultRoot1, resultLeftPart + resultRightPart, resultLeftPart - resultRightPart };
            }
        }

        throw new ArithmeticException("Unreachable state reached.");
    }
    
}