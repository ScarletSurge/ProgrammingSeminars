using RGU.dotNET.SecondTerm.GC;

Console.WriteLine("Hello, World!");

{
    using var obj = new ResourceHolder("file.txt");
    //
    throw new NotImplementedException();
    obj.Dispose();
    // TODO: work with object...
    //
}

{
    ResourceHolder obj = null;
    try
    {
        obj = new ResourceHolder("file.txt");
        //
        throw new NotImplementedException();
        obj.Dispose();
        // TODO: work with object...
        //
    }
    finally
    {
        obj?.Dispose();
    }
    //
}

// 