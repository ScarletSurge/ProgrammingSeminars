using System;
using System.IO;

namespace Practice.Core
{
    
    // ICloneable, IEquatable<T>, IComparable, IComparable<T>,
    // IComparer<T>, IEqualityComparer<T>, IDisposable,
    // IEnumerator, IEnumerator<T>, IEnumerable, IEnumerable<T>

    public class VeryHardToUnderstandObject : ICloneable
    {
        // TODO: a lot of data & functionality

        public object Clone()
        {
            return new VeryHardToUnderstandObject()
            {
                // TODO: some initialization for deep copy
            };
        }
    }

    public sealed class CloneableImplementation : ICloneable
    {

        private int _field1;
        private string _field2;
        private VeryHardToUnderstandObject _field3;

        public object Clone()
        {
            return new CloneableImplementation
            {
                _field1 = _field1,
                _field2 = _field2,
                _field3 = _field3.Clone() as VeryHardToUnderstandObject
            };
        }

    }

    public class LogContext : IDisposable
    {
        
        #region Nested
        
        private sealed class DisposableImplementation : IDisposable
        {

            private StreamWriter _logWriter;

            public DisposableImplementation(string filePath)
            {
                _logWriter = new StreamWriter(filePath);
            }

            public void Log(string logMessage)
            {
                _logWriter.WriteLine($"[{DateTime.Now:G}]: {logMessage}");
            }

            public void Dispose()
            {
                _logWriter.Dispose();
            }
        
        }
        
        #endregion
        
        private DisposableImplementation _d;

        public LogContext(string filePath)
        {
            _d = new DisposableImplementation(filePath);
        }

        public void Log(string message)
        {
            _d.Log(message);
        }

        public void Dispose()
        {
            _d.Dispose();
            GC.SuppressFinalize(this);
        }

        ~LogContext()
        {
            _d.Dispose();
        }
        
    }
    
}