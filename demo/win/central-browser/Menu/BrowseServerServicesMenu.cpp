#include "BrowseServerServicesMenu.h"

#include <memory>
#include <string>

using namespace std;
using namespace Bluetooth;

namespace Console
{
	BrowseServerServicesMenu::BrowseServerServicesMenu(const Menu * parent, const Serial::ISerial& serial)
		: BluetoothMenu(parent, "Browse Server Services", serial)
	{
	}

	void BrowseServerServicesMenu::Reload()
	{
		Clear();

		UUID services[20];
		uint8_t listed = 0;
		if (!m_Device.GetDriver().ListServerServices(services, 20, &listed))
			return;

		for (uint8_t i = 0; i < listed; ++i)
		{
			char buf[32];
			snprintf(buf, sizeof(buf), "%04X", services[i].GetShortUUID());

			AddItem(unique_ptr<MenuItem>(make_unique<EmptyItem>(buf)));
		}
	}
}
