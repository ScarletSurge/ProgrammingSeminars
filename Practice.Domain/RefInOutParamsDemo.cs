namespace Practice.Domain;

public static class RefInOutParamsDemo
{
    public static void NoRefValueDemo(
        int value)
    {
        value = 20;
    }
    
    public static void RefValueDemo(
        ref int value)
    {
        value = 20;
    }
    
    public static void OutValueDemo(
        out int value)
    {
        value = 20;
    }

    public static void NoRefRefDemo(
        string value)
    {
        value = nameof(NoRefRefDemo);
    }

    public static void RefRefDemo(
        ref string value)
    {
        value = nameof(RefRefDemo);
    }
    
    public static void OutRefDemo(
        out string value)
    {
        value = nameof(OutRefDemo);
    }
    
    /// <summary>
    /// Вычислить среднее арифметическое элементов.
    /// </summary>
    /// <param name="values">Коллекция элементов.</param>
    /// <returns>Среднее арифметическое элементов.</returns>
    /// <exception cref="ArgumentNullException">Ссылка на массив == null.</exception>
    /// <exception cref="ArgumentException">Массив имеет длину 0.</exception>
    public static double Average(
        params int[] values)
    {
        if (values is null)
        {
            throw new ArgumentNullException(nameof(values));
        }
        
        if (values.Length == 0)
        {
            throw new ArgumentException(nameof(values));
        }

        int sum = 0;
        for (int i = 0; i < values.Length; i++)
        {
            sum += values[i];
        }

        return (double)sum / values.Length;
    }
}