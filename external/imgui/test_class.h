/*  
*	Testing new window for modifiying mesh layers
*/

#include "VulkanglTFModel.h"
#include "vulkanexamplebase.h"

class TestWindow
{
  public:
	/*vkglTF::Node a;
	vkglTF::Node b;
	vkglTF::Node c;
	
	vkglTF::Node *newNode = new Node{};
	newNode->index = nodeIndex;
	newNode->parent = parent;
	newNode->name = node.name;
	newNode->skinIndex = node.skin;
	newNode->matrix = glm::mat4(1.0f);
	*/

	void testFrame()
	{
		vkglTF::Node *nodeA = new vkglTF::Node{};
		nodeA->index        = 0;
		nodeA->name         = "Mesh 1";
		vkglTF::Node *nodeB = new vkglTF::Node{};
		nodeB->index        = 1;
		nodeB->name         = "Mesh 2";
		vkglTF::Node *nodeC = new vkglTF::Node{};
		nodeC->index        = 2;
		nodeC->name         = "Mesh 3";

		std::vector<vkglTF::Node>   nodes;
		//std::array<vkglTF::Node, 3> nodes;
		nodes = {*nodeA, *nodeB, *nodeC};

		static bool  testBool   = false;
		static bool *selections = new bool[nodes.size()];

		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
		ImGui::Begin("Testing - Xavier");

		//Setup for TreeNodes with selectable children
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_DefaultOpen;
		if (ImGui::TreeNodeEx("Nodes with Selectable Children Meshes", node_flags))
		{
			static int clicked = 0;
			if (ImGui::Button("Add Node"))
				clicked++;
			if (clicked & 1)
			{
				addNode(nodes);
			}

			for (const vkglTF::Node node : nodes)
			{
				if (ImGui::TreeNode((void *) (intptr_t) node.index, "Node - %d", node.index))
				{
					std::string nodeLabelTemp ("Mesh - ");
					std::string nodeLabel = nodeLabelTemp + node.name.c_str();
					ImGui::Selectable(nodeLabel.c_str(), &selections[node.index]);
					//ImGui::Checkbox("Node with checkbox", &testBool);

					static int clicked = 0;
					if (ImGui::Button("Remove Node"))
						clicked++;
					if (clicked & 1)
					{

					}
					ImGui::TreePop();
				}

			
			}
			ImGui::TreePop();
		}

		//Setup for Selectable TreeNodes with details as children
		if (ImGui::TreeNodeEx("Selectable Nodes with details as Children", node_flags))
		{
			static int selection_mask = (1 << 10);
			int        node_clicked   = -1;
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);
			for (vkglTF::Node node : nodes)
			{
				ImGuiTreeNodeFlags node_flags2 = ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << node.index)) ? ImGuiTreeNodeFlags_Selected : 0);
				if (node.index < 3)
				{
					// Node
					bool node_open = ImGui::TreeNodeEx((void *) (intptr_t) node.index, node_flags2, "Selectable Node %d", node.index);
					if (ImGui::IsItemClicked())
						node_clicked = node.index;

					if (node_open)
					{
						ImGui::Text("Mesh Details\nMore Mesh Details");
						ImGui::TreePop();
					}
				}
			}
			if (node_clicked != -1)
			{
				//if (ImGui::GetIO().KeyShift)
					selection_mask ^= (1 << node_clicked);                          
			}
			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
		ImGui::End();
	}

	bool addNode(std::vector<vkglTF::Node> nodes)
	{
		//collect node data somehow and add it to nodes
		return true;
	}

	void removeNode(vkglTF::Node nodes[], vkglTF::Node lessNode)
	{

	}
};