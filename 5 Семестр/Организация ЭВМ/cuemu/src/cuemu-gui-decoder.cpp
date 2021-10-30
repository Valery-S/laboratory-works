#include "cuemu-gui-decoder.h"
#include "cuemu-rc.rh"
#include "cuemu.h"
#pragma hdrstop
#pragma warn -csu
#include <vector>
#include <algorithm>

TCuemuDecoder::TCuemuDecoder(TWindow *parent)
: TDialog(parent, "DECODER")
{
 tree = new TTreeWindow(this, IDC_MOPTREE);
}

void TCuemuDecoder::Update()
{
 tree->DeleteAllItems();
 if (!list) return;
 std::vector<int> addresses;
 microcommand *l = list;
 do {
  addresses.push_back(l->addr);
  l = l->next;
 } while (l!=list);
 std::sort(addresses.begin(), addresses.end());
 tree->GetRoot().ExpandItem(TTreeNode::Expand);
 for (std::vector<int>::const_iterator i=addresses.begin(); i!=addresses.end(); i++) {
  char buf[256];
  if (*i!=addr) {
   sprintf(buf, "����� %d", (int)*i);
  } else {
   sprintf(buf, "����� %d - �������", addr);
  }
  TTreeNode node(*tree, buf);
  TTreeNode res = tree->GetRoot().AddChild(node);
  if (*i==addr) res.SetState(TVIS_BOLD);
  microcommand *mc = search_addr(list, *i);
  qword cmd = mc->cmd;
  for (int i=1; i<=38; i++, cmd>>=1) {
   if (cmd & 1) {
    cmdinfo *x = find_command((uint8)i);
    if (!x) continue;
    sprintf(buf, "%d: %s", i, x->name);
    res.AddChild(TTreeNode(*tree, buf));
   }
  }
  sprintf(buf, "����������� �������: %u", GET_CONDITION(mc->cmd));
  res.AddChild(TTreeNode(*tree, buf));
  sprintf(buf, "����� 1: %u", GET_ADDR1(mc->cmd));
  res.AddChild(TTreeNode(*tree, buf));
  sprintf(buf, "����� 2: %u", GET_ADDR2(mc->cmd));
  res.AddChild(TTreeNode(*tree, buf));
  sprintf(buf, "����� ������ �������: %u", GET_GROUP(mc->cmd));
  res.AddChild(TTreeNode(*tree, buf));  
  res.ExpandItem(TTreeNode::Expand);
  res.SetItem();  
 }
}
