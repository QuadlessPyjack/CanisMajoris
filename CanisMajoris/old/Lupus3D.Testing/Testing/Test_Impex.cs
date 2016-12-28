using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using Lupus3D.FileInfo;

namespace Lupus3D.Testing
{
	public class Test_Impex
	{
		private Model testModel = new Model();
		private TestContainer container;
		private string modelFileName = "test_model.l3d";
		public int numberOfTests { get { return 3; } }

		public Test_Impex()
		{
			container = new TestContainer();
		}

		public bool SaveTest()
		{
			testModel.AddMesh(container.test_mesh1);
			
			if (!testModel.SaveFile(modelFileName))
			{
				return false;
			}

			if(!File.Exists(modelFileName))
			{
				return false;
			}

			return true;
		}

		public bool LoadTest()
		{
			testModel = new Model();
			return testModel.LoadFile(modelFileName);
		}

		public error PersistenceTest()
		{
			testModel = new Model();
			
			if (!testModel.LoadFile(modelFileName))
			{
				return new error(true, "File loading failed.");
			}
			
			MeshFile[] meshes = testModel.ExtractMeshData();
			
			if (container.MeshCompare(meshes[0], container.test_mesh1).status)
			{
				return new error(true, "Mesh comparison failed. Reason: \n" + container.MeshCompare(meshes[0], container.test_mesh1).message);
			}

			return new error(false);
		}
	}
}
