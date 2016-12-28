using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Lupus3D.FileInfo;

namespace Lupus3D.Testing
{
	public class TestContainer
	{
		public string errorBuffer = "";
		public MeshFile test_mesh1 = new MeshFile();

		private VertexFile vx1 = new VertexFile();
		private VertexFile vx2 = new VertexFile();
		private VertexFile vx3 = new VertexFile();

		private EdgeFile e1 = new EdgeFile();
		private EdgeFile e2 = new EdgeFile();
		private EdgeFile e3 = new EdgeFile();

		private TriangleFile t1 = new TriangleFile();

		private string MESH_NAME = "TEST_MESH_1";
		
		public TestContainer()
		{
			vx1.m_v3 = CreateCustomVector3(1.0f, 2.0f, 3.0f);
			vx1.m_wsTransform = CreateCustomVector3(-3.2f, -2.1f, -1.9f);
			vx1.m_id = 1;
			vx1.m_meshOwnerName = MESH_NAME;
			vx1.m_dirtyFlag = true;

			vx2.m_v3 = CreateCustomVector3(-1.0f, 4.0f, -3.0f);
			vx2.m_wsTransform = CreateCustomVector3(32.0f, 21.0f, 19.0f);
			vx2.m_meshOwnerName = MESH_NAME;
			vx2.m_id = 2;
			vx2.m_dirtyFlag = false;

			vx3.m_v3 = CreateCustomVector3(1.5f, 1.6f, 1.7f);
			vx3.m_wsTransform = CreateCustomVector3(-23.0f, 12.0f, 9.1f);
			vx3.m_meshOwnerName = MESH_NAME;
			vx3.m_id = 3;
			vx3.m_dirtyFlag = true;

			e1.m_startVert = vx1;
			e1.m_endVert = vx2;
			e1.m_index = 0;
			e1.m_mesh_owner = test_mesh1;
			e1.m_ownerTriangleIDs = new int[] { 34343 };

			e2.m_startVert = vx2;
			e2.m_endVert = vx3;
			e2.m_index = 1;
			e2.m_mesh_owner = test_mesh1;
			e2.m_ownerTriangleIDs = new int[] { 34343 };

			e3.m_startVert = vx3;
			e3.m_endVert = vx1;
			e3.m_index = 2;
			e3.m_mesh_owner = test_mesh1;
			e3.m_ownerTriangleIDs = new int[] { 34343 };

			t1.m_edgeA = e1;
			t1.m_edgeB = e2;
			t1.m_edgeC = e3;
			t1.m_id = 34343;

			test_mesh1.meshID = MESH_NAME;
			test_mesh1.m_localVerts = new VertexFile[] { vx1, vx2, vx3 };
			test_mesh1.m_localEdges = new EdgeFile[] { e1, e2, e3 };
			test_mesh1.m_localTris = new TriangleFile[] { t1 };

			test_mesh1.m_triCount = 1;
			test_mesh1.m_vertCount = 3;
			test_mesh1.m_scaleFactor = 1.0f;
			test_mesh1.m_colour = CreateCustomVector3(0.0f, 255.0f, 255.0f);
			test_mesh1.m_pivot = CreateCustomVector3(0.0f, 0.0f, 0.0f);
			test_mesh1.m_wsPivot = CreateCustomVector3(3434.0f, 4584.0f, 123.0f);
			test_mesh1.m_wsRotation = CreateCustomVector3(128.0f, 345.0f, 890.0f);
			test_mesh1.m_dirtyFlag = true;
		}

		public error MeshCompare(MeshFile mesh1, MeshFile mesh2)
		{
			if (mesh1.meshID != mesh2.meshID)
			{
				return new error(true, String.Format("* Mesh ID mismatch. Expected {0}, got {1}", mesh1.meshID, mesh2.meshID));
			}

			if (V3Compare(mesh1.m_colour, mesh2.m_colour).status)
			{
				return new error(true, String.Format("* Mesh colour mismatch. \n*{0}", V3Compare(mesh1.m_colour, mesh2.m_colour).message));
			}

			if (mesh1.m_dirtyFlag != mesh2.m_dirtyFlag)
			{
				return new error(true, String.Format("* Mesh dirty flag mismatch. Expected {0}, got {1}", mesh1.m_dirtyFlag, mesh2.m_dirtyFlag));
			}

			if (ArrayCompare<EdgeFile>(mesh1.m_localEdges, mesh2.m_localEdges).status)
			{
				return new error(true, String.Format("* Mesh edge array mismatch. \n*{0}", ArrayCompare<EdgeFile>(mesh1.m_localEdges, mesh2.m_localEdges).message));
			}

			if (ArrayCompare<VertexFile>(mesh1.m_localVerts, mesh2.m_localVerts).status)
			{
				return new error(true, String.Format("* Mesh vertex array mismatch. \n*{0}", ArrayCompare<VertexFile>(mesh1.m_localVerts, mesh2.m_localVerts).message));
			}

			if (ArrayCompare<TriangleFile>(mesh1.m_localTris, mesh2.m_localTris).status)
			{
				return new error(true, String.Format("* Mesh triangle array mismatch. \n*{0}", ArrayCompare<TriangleFile>(mesh1.m_localTris, mesh2.m_localTris).message));
			}

			if (V3Compare(mesh1.m_pivot, mesh2.m_pivot).status)
			{
				return new error(true, String.Format("* Mesh pivot mismatch. \nReason: {0}", V3Compare(mesh1.m_pivot, mesh2.m_pivot).message));
			}

			if (mesh1.m_triCount != mesh2.m_triCount)
			{
				return new error(true, String.Format("* Mesh triangle count mismatch. Expected {0}, got {1}", mesh1.m_triCount, mesh2.m_triCount));
			}

			if (mesh1.m_vertCount != mesh2.m_vertCount)
			{
				return new error(true, String.Format("* Mesh vertex count mismatch. Expected {0}, got {1}", mesh1.m_vertCount, mesh2.m_vertCount));
			}

			if (V3Compare(mesh1.m_wsPivot, mesh2.m_wsPivot).status)
			{
				return new error(true, String.Format("* Mesh world pivot mismatch. \n*{0}", V3Compare(mesh1.m_wsPivot, mesh2.m_wsPivot).message));
			}

			if (V3Compare(mesh1.m_wsRotation, mesh2.m_wsRotation).status)
			{
				return new error(true, String.Format("* Mesh world rotation mismatch. \n*{0}", V3Compare(mesh1.m_wsRotation, mesh2.m_wsRotation).message));
			}

			return new error(false);
		}

		public error ArrayCompare<T>(T[] a1, T[] a2)
		{
			if (a1 == null || a2 == null)
			{
				return new error(true, "* Array Nullcheck failed.");
			}

			if (a1.Length != a2.Length)
			{
				return new error(true, "* Array length mismatch.");
			}

			for (int index = 0; index < a1.Length; ++index)
			{
				if (!a1[index].Equals(a2[index]))
				{
					return new error(true, String.Format("* Array member mismatch, index {0} ( {1} != {2})", index, a1[index], a2[index]));
				}
			}

			return new error(false);
		}

		public error V3Compare(Vector3File v3_1, Vector3File v3_2)
		{
			if (v3_1.x != v3_2.x)
			{
				return new error(true, String.Format("* Vector X member mismatch. Expected {0}, got {1}", v3_1.x, v3_2.x));
			}

			if (v3_1.y != v3_2.y)
			{
				return new error(true, String.Format("* Vector X member mismatch. Expected {0}, got {1}", v3_1.y, v3_2.y));
			}

			if (v3_1.z != v3_2.z)
			{
				return new error(true, String.Format("* Vector X member mismatch. Expected {0}, got {1}", v3_1.z, v3_2.z));
			}

			return new error(false);
		}

		public error VertexCompare(VertexFile vx1, VertexFile vx2)
		{
			if (vx1.m_id != vx2.m_id)
			{
				return new error(true, String.Format("* Vertex ID mismatch. Expected {0}, got {1}", vx1.m_id, vx2.m_id));
			}

			if (vx1.m_meshOwnerName != vx2.m_meshOwnerName)
			{
				return new error(true, String.Format("* Vertex mesh owner name mismatch. Expected {0}, got {1}", vx1.m_meshOwnerName, vx2.m_meshOwnerName));
			}

			if (vx1.m_dirtyFlag != vx2.m_dirtyFlag)
			{
				return new error(true, String.Format("* Vertex dirty flag mismatch. Expected {0}, got {1}", vx1.m_dirtyFlag, vx2.m_dirtyFlag));
			}

			if (V3Compare(vx1.m_v3, vx2.m_v3).status)
			{
				return new error(true, "* Vertex local transform mismatch. \n*" + V3Compare(vx1.m_v3, vx2.m_v3).message);
			}

			if (V3Compare(vx1.m_wsTransform, vx2.m_wsTransform).status)
			{
				return new error(true, "* Vertex world transform mismatch. \n*" + V3Compare(vx1.m_wsTransform, vx2.m_wsTransform).message);
			}

			return new error(false);
		}

		public error EdgeCompare(EdgeFile e1, EdgeFile e2)
		{
			if (e1.m_index != e2.m_index)
			{
				return new error(true, String.Format("* Edge index mismatch. Expected {0}, got {1}", e1.m_index, e2.m_index));
			}

			if (e1.m_mesh_owner != e2.m_mesh_owner)
			{
				return new error(true, String.Format("* Mesh owner mismatch. Expected {0}, got {1}", e1.m_mesh_owner, e2.m_mesh_owner));
			}

			if (ArrayCompare<int>(e1.m_ownerTriangleIDs, e2.m_ownerTriangleIDs).status)
			{
				return new error(true, "* Owning Triangle IDs Array comparison failed. \n*" + ArrayCompare<int>(e1.m_ownerTriangleIDs, e2.m_ownerTriangleIDs).message);
			}

			if (VertexCompare(e1.m_startVert, e2.m_startVert).status)
			{
				return new error(true, "* Edge start vertex mismatch. \n*" + VertexCompare(e1.m_startVert, e2.m_startVert).message);
			}

			if (VertexCompare(e1.m_endVert, e2.m_endVert).status)
			{
				return new error(true, "* Edge end vertex mismatch. \n*" + VertexCompare(e1.m_endVert, e2.m_endVert).message);
			}

			return new error(false);
		}

		public error TriangleCompare(TriangleFile t1, TriangleFile t2)
		{
			if (t1.m_id != t2.m_id)
			{
				return new error(true, String.Format("* Triangle ID mismatch. Expected {0}, got {1}", t1.m_id, t2.m_id));
			}

			if (EdgeCompare(t1.m_edgeA, t2.m_edgeA).status)
			{
				return new error(true, "* Edge A mismatch: \n*" + EdgeCompare(t1.m_edgeA, t2.m_edgeA).message);
			}

			if (EdgeCompare(t1.m_edgeB, t2.m_edgeB).status)
			{
				return new error(true, "* Edge B mismatch: \n*" + EdgeCompare(t1.m_edgeB, t2.m_edgeB).message);
			}

			if (EdgeCompare(t1.m_edgeC, t2.m_edgeC).status)
			{
				return new error(true, "* Edge C mismatch: \n*" + EdgeCompare(t1.m_edgeC, t2.m_edgeC).message);
			}

			return new error(false);
		}

		private Vector3File CreateCustomVector3(float x, float y, float z)
		{
			Vector3File v3 = new Vector3File();
			v3.x = x;
			v3.y = y;
			v3.z = z;

			return v3;
		}
	}

	public struct error
	{
		public bool status;
		public string message;

		public error(bool hasFailed, string reason)
		{
			status = hasFailed;
			message = reason;
		}

		public error(bool hasFailed)
		{
			status = hasFailed;
			message = "";
		}
	}
}
