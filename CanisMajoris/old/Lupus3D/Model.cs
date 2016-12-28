using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;

using Lupus3D.FileInfo;

namespace Lupus3D
{
    public static class Model
    {
		public static MeshFile[] ExtractMeshData()
		{
			return m_meshes.ToArray();
		}

		public static void AddMesh(MeshFile meshFile)
		{
			m_meshes.Add(meshFile);
		}

		public static bool LoadFile(string filePath)
		{
			if (!File.Exists(filePath))
			{
				return false;
			}

			IFormatter formatterDeserializer = new BinaryFormatter();
			formatterDeserializer.Binder = new BinaryTranscoderBinder();

			m_fileStream = new FileStream(filePath, FileMode.Open);
			try
			{
				m_meshArray = ((MeshFile[])Convert.ChangeType(formatterDeserializer.Deserialize(m_fileStream),
															  typeof(MeshFile[]))
								);

				m_meshes.AddRange(m_meshArray.ToList());
				
			}
			catch (System.Exception e)
			{
				Console.WriteLine("Unable to load model file: access error or malformed file!");
				Console.WriteLine(e);

				return false;
			}

			m_fileStream.Close();
			return true;
		}

		public static bool SaveFile(string filePath)
		{
			IFormatter formatterSerializer = new BinaryFormatter();
			formatterSerializer.Binder = new BinaryTranscoderBinder();
			try
			{
			    m_fileStream = new FileStream(filePath, FileMode.Create);
			    formatterSerializer.Serialize(m_fileStream, m_meshes.ToArray());

			    m_fileStream.Close();
			    m_fileStream.Dispose();
			}
			catch (System.Exception e)
			{
			    Console.WriteLine("Unable to save model file: write or serialization error!");
				Console.WriteLine(e);
			    return false;
			}

			return true;
		}

		public static bool isValid()
		{
			if(m_meshes.Count != 0)
			{
				return true;
			}

			return false;
		}

		private static FileStream m_fileStream;

		private static List<MeshFile> m_meshes = new List<MeshFile>();
		private static MeshFile[] m_meshArray;
    }

	public sealed class BinaryTranscoderBinder : SerializationBinder
	{
		public override Type BindToType(string assemblyName, string typeName)
		{

			if (!string.IsNullOrEmpty(assemblyName) && !string.IsNullOrEmpty(typeName))
			{

				Type typeToDeserialize = null;
				assemblyName = Assembly.GetExecutingAssembly().FullName;

				// The following line of code returns the type.
				typeToDeserialize = Type.GetType(String.Format("{0}, {1}", typeName, assemblyName));
				return typeToDeserialize;
			}
			return null;
		}
	}
}