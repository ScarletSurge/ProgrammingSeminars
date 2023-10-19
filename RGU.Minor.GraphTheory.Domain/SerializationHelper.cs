﻿using System.Text;

namespace RGU.Minor.GraphTheory.Domain;

public static class SerializationHelper
{
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public static byte[] ToByteArray(
        this string value)
    {
        using var stream = new MemoryStream();
        value.ToStream(stream);
        var result = stream.GetBuffer();
        Array.Resize(ref result, sizeof(int) + sizeof(char) * value.Length);
        return result;
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <param name="stream"></param>
    public static void ToStream(
        this string value,
        Stream stream)
    {
        stream.Write(BitConverter.GetBytes(value.Length));
        stream.Write(value
            .ToCharArray()
            .SelectMany(BitConverter.GetBytes)
            .ToArray());
    }
    
    /// <summary>
    /// 
    /// </summary>
    /// <param name="stream"></param>
    /// <returns></returns>
    public static string StringFromMemoryStream(
        this Stream stream)
    {
        var destination = new byte[sizeof(int)];
        stream.Read(destination, 0, destination.Length);
        var charsCount = BitConverter.ToInt32(destination, 0);

        destination = new byte[sizeof(char) * charsCount];
        stream.Read(destination, 0, destination.Length);

        return Encoding.Unicode.GetString(destination);
    }
        
}