#include "pch.h"
#include "UI.h"


UI::UI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_Parent(nullptr)
	, m_bModal(false)
{
}

UI::~UI()
{
	Delete_Vec(m_vecChildUI);
}

void UI::ButtonTitle(const char* _name)
{
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::Button(_name);

	ImGui::PopStyleColor(3);
	ImGui::PopID();
	ImGui::SameLine();
}

// ������ �˻� ������ �޺� �ڽ� ����
bool UI::SearchableComboBox(const char* id, int* current_item, std::vector<std::string>& items) {
	// �˻� ���ڿ��� ������ ����
	static char searchBuffer[256] = "";

	// �޺� �ڽ��� �˻� �ʵ��� ���� ID�� �����ϱ� ���� ����ڰ� ������ id�� ���
	std::string combo_box_id = std::string("##ComboBox") + id;
	std::string search_field_id = std::string("##SearchField") + id;

	// �˻� �ʵ�
	ImGui::InputText(search_field_id.c_str(), searchBuffer, IM_ARRAYSIZE(searchBuffer));

	if (ImGui::BeginCombo(combo_box_id.c_str(), items[*current_item].c_str())) {
		for (int i = 0; i < items.size(); i++) {
			// �˻�� ��� ���� �ʰ� �׸��� �˻�� �������� �ʴ� ��� �ǳʶڴ�

			string lowerItem = items[i];
			std::transform(lowerItem.begin(), lowerItem.end(), lowerItem.begin(), [](unsigned char c) { return std::tolower(c); });

			string lowersearch = searchBuffer;
			std::transform(lowersearch.begin(), lowersearch.end(), lowersearch.begin(), [](unsigned char c) { return std::tolower(c); });

			if (searchBuffer[0] != '\0' && lowerItem.find(lowersearch) == std::string::npos) {
				continue;
			}

			// �׸� ���� �����ϰ� �����
			bool is_selected = (*current_item == i);
			if (ImGui::Selectable(items[i].c_str(), is_selected)) {
				*current_item = i;
			}

			// �׸��� ���õ� ���, �޺� �ڽ��� �ݰ� �ش� �׸����� ��ũ���ϱ�
			if (is_selected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	return true;
}


void UI::tick()
{

}

void UI::render()
{
	if (!m_bActive)
		return;

	bool Active = m_bActive;

	if (nullptr == GetParentUI())
	{
		// Modal
		if (!m_bModal)
		{
			ImGui::Begin(string(m_strName + m_strID).c_str(), &Active);

			// Ȱ��ȭ, ��Ȱ��ȭ ��ȯ�� �߻��� ��쿡�� Activate or Deactivate �� ȣ���Ų��.
			if (Active != m_bActive)
			{
				m_bActive = Active;

				if (m_bActive)
					Activate();
				else
					Deactivate();
			}

			render_update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				m_vecChildUI[i]->render();
			}

			ImGui::End();
		}

		// Modal
		else
		{
			ImGui::OpenPopup(string(m_strName + m_strID).c_str());
			if (ImGui::BeginPopupModal(string(m_strName + m_strID).c_str(), &Active))
			{
				render_update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					m_vecChildUI[i]->render();
				}

				ImGui::EndPopup();
			}

			else
			{
				// Ȱ��ȭ, ��Ȱ��ȭ ��ȯ�� �߻��� ��쿡�� Activate or Deactivate �� ȣ���Ų��.
				if (Active != m_bActive)
				{
					m_bActive = Active;

					if (m_bActive)
						Activate();
					else
						Deactivate();
				}
			}
		}		
	}

	// Child UI �� ���
	else
	{
		ImGui::BeginChild(string(m_strName + m_strID).c_str(), m_vSize);

		render_update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->render();
		}

		ImGui::EndChild();
	}
}