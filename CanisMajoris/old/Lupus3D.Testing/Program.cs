using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lupus3D.Testing
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Initiating Lupus 3D Library Test Container");
			Test_Impex l3dLibTest = new Test_Impex();
			int passedTests = 0;

			Console.Write("Running file save test... ");
			bool hasPassed = l3dLibTest.SaveTest();
			if(hasPassed)
			{
				Console.ForegroundColor = ConsoleColor.Green;
				Console.WriteLine("passed");
				passedTests++;
			}
			else
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine("failed");
			}

			Console.ResetColor();
			Console.Write("Running file load test... ");
			hasPassed = l3dLibTest.LoadTest();
			if (hasPassed)
			{
				Console.ForegroundColor = ConsoleColor.Green;
				Console.WriteLine("passed");
				passedTests++;
			}
			else
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine("failed");
			}

			Console.ResetColor();
			Console.Write("Running persistence test... ");
			error testErrorStatus = l3dLibTest.PersistenceTest();
			hasPassed = !testErrorStatus.status;

			if (hasPassed)
			{
				Console.ForegroundColor = ConsoleColor.Green;
				Console.WriteLine("passed");
				passedTests++;
			}
			else
			{
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine("failed");
				Console.WriteLine("Details: ");
				Console.WriteLine(testErrorStatus.message);
			}

			Console.ResetColor();
			Console.WriteLine("{0}/{1} Tests passed.", passedTests, l3dLibTest.numberOfTests);
			Console.ReadKey();
		}
	}
}
