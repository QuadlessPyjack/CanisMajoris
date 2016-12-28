using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lupus3D.FileInfo
{
	[System.Serializable]
	public class MeshFile
	{
		public string meshID;
		public VertexFile[] m_localVerts = new VertexFile[] {};
		public EdgeFile[] m_localEdges = new EdgeFile[] {};
		public TriangleFile[] m_localTris = new TriangleFile[] {};

		public int m_triCount;
		public int m_vertCount;
		public float m_scaleFactor;
		public Vector3File m_wsRotation;
		public Vector3File m_wsPivot;
		public Vector3File m_pivot;
		public Vector3File m_colour;
		public BoundsFile m_boundingBox;

		public bool m_dirtyFlag;
	}

	[System.Serializable]
	public class TriangleFile
	{
		public int m_id;
		public EdgeFile m_edgeA;
		public EdgeFile m_edgeB;
		public EdgeFile m_edgeC;

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}

			TriangleFile t1 = obj as TriangleFile;
			if ((System.Object)t1 == null)
			{
				return false;
			}

			if (!m_edgeA.Equals(t1.m_edgeA))
			{
				return false;
			}

			if (!m_edgeB.Equals(t1.m_edgeB))
			{
				return false;
			}

			if (!m_edgeC.Equals(t1.m_edgeC))
			{
				return false;
			}

			return true;
		}
	}

	[System.Serializable]
	public class EdgeFile
	{
		public int[] m_ownerTriangleIDs = new int[2];
		public int m_index;
		public MeshFile m_mesh_owner;
		public VertexFile m_startVert;
		public VertexFile m_endVert;

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}

			EdgeFile e1 = obj as EdgeFile;
			if ((System.Object)e1 == null)
			{
				return false;
			}

			if (m_index != e1.m_index)
			{
				return false;
			}

			if (m_ownerTriangleIDs == null || e1.m_ownerTriangleIDs == null)
			{
				return false;
			}

			if (m_ownerTriangleIDs.Length != e1.m_ownerTriangleIDs.Length)
			{
				return false;
			}

			for (int index = 0; index < m_ownerTriangleIDs.Length; index++)
			{
				if (m_ownerTriangleIDs[index] != e1.m_ownerTriangleIDs[index])
				{
					return false;
				}
			}

			if (m_mesh_owner.meshID != e1.m_mesh_owner.meshID)
			{
				return false;
			}

			if (m_startVert.m_id != e1.m_startVert.m_id)
			{
				return false;
			}

			if (m_endVert.m_id != e1.m_endVert.m_id)
			{
				return false;
			}
			
			return true;
		}
	}

	[System.Serializable]
	public class VertexFile
	{
		public VertexFile()
		{
			m_id = 0;
			m_dirtyFlag = false;
			m_meshOwnerName = "NULL";
			m_v3 = new Vector3File();
			m_wsTransform = new Vector3File();
		}

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}

			VertexFile vx1 = obj as VertexFile;
			if ((System.Object)vx1 == null)
			{
				return false;
			}

			if (m_id != vx1.m_id)
			{
				return false;
			}

			if (m_meshOwnerName != vx1.m_meshOwnerName)
			{
				return false;
			}

			if (!m_v3.Equals(vx1.m_v3))
			{
				return false;
			}

			if (!m_wsTransform.Equals(vx1.m_wsTransform))
			{
				return false;
			}

			return true;
		}

		public int m_id;
		public bool m_dirtyFlag;
  
		public string m_meshOwnerName;
		public Vector3File m_v3;
		public Vector3File m_wsTransform;
	}

	[System.Serializable]
	public class Vector3File
	{
		public Vector3File()
		{
			x = 0.0f; y = 0.0f; z = 0.0f;
		}

		public override bool Equals(object obj)
		{
			if (obj == null)
			{
				return false;
			}

			Vector3File v3 = obj as Vector3File;
			if ((System.Object)v3 == null)
			{
				return false;
			}

			if (x != v3.x || y != v3.y || z != v3.z)
			{
				return false;
			}

			return true;
		}

		public float x;
		public float y;
		public float z;
	}

	[System.Serializable]
	public struct BoundsFile
	{
		public BoundsFile(Vector3File min, Vector3File max) { minCorner = min; maxCorner = max; }

		Vector3File minCorner;
		Vector3File maxCorner;
	};
}
