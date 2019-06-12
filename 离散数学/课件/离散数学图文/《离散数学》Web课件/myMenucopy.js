/******************************************************************************
* This file defines the tree menu with it's items and submenus.               *
******************************************************************************/

// User-defined tree menu data.

var treeMenu           = new TreeMenu();  // This is the main menu.
var treeMenuName       = "myMenu_2.0";    // Make this unique for each tree menu.
var treeMenuDays       = 7;               // Number of days to keep the cookie.
var treeMenuFrame      = "mulu";          // Name of the menu frame.
var treeMenuImgDir     = "graphics/"      // Path to graphics directory.
var treeMenuBackground = "Image/di.gif";              // Background image for menu frame.   
var treeMenuBgColor    = "";       // Color for menu frame background.   
var treeMenuFgColor    = "#000000";       // Color for menu item text.
var treeMenuHiBg       = "#008080";       // Color for selected item background.
var treeMenuHiFg       = "#ffffff";       // Color for selected item text.
var treeMenuFont       = 
      "MS Sans Serif,Arial,Helvetica,Time New Roman";    // Text font face.
var treeMenuFontSize   = 1;               // Text font size.
var treeMenuRoot       = "��ɢ��ѧ";      // Text for the menu root.
var treeMenuFolders    = 0;               // Sets display of '+' and '-' icons.
var treeMenuAltText    = true;            // Use menu item text for icon image ALT text.

// Define the items for the top-level of the tree menu.

//ȫ��Ŀ¼
//treeMenu.addItem(new TreeMenuItem("����","content-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("��һ�� �����߼�","content-1-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("�ڶ��� ν���߼�","content-2-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("������ ����","content-3-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("������ ��Ԫ��ϵ","content-4-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("������ ����","content-5-0.htm","content"));
treeMenu.addItem(new TreeMenuItem("������ ����ϵͳ","content-6-0.htm","content"));
//treeMenu.addItem(new TreeMenuItem("���ڱ��μ�","about.htm","content"));

//��һ��
var chap_1 = new TreeMenu();
chap_1.addItem(new TreeMenuItem("��һ�� ����","content-1-1.htm","content"));
chap_1.addItem(new TreeMenuItem("�ڶ��� �ж�����","content-1-2.htm","content"));
chap_1.addItem(new TreeMenuItem("������ ����","content-1-3.htm","content"));
treeMenu.items[0].makeSubmenu(chap_1);
//��һ�µ�һ��
var chap_1_1 = new TreeMenu();
chap_1_1.addItem(new TreeMenuItem("����", "content-1-1-1.htm", "content"));
chap_1_1.addItem(new TreeMenuItem("�����", "content-1-1-2.htm", "content"));
chap_1_1.addItem(new TreeMenuItem("���⹫ʽ", "content-1-1-3.htm", "content"));
chap_1_1.addItem(new TreeMenuItem("����ϰ��", "content-1-1-x.htm", "content"));
chap_1.items[0].makeSubmenu(chap_1_1);
//��һ�µڶ���
var chap_1_2 = new TreeMenu();
chap_1_2.addItem(new TreeMenuItem("�����Ĺ�ϵ", "content-1-2-1.htm", "content"));
chap_1_2.addItem(new TreeMenuItem("��ʽ", "content-1-2-2.htm", "content"));
chap_1_2.addItem(new TreeMenuItem("����ϰ��", "content-1-2-x.htm", "content"));
chap_1.items[1].makeSubmenu(chap_1_2);
//��һ�µ�����
var chap_1_3 = new TreeMenu();
chap_1_3.addItem(new TreeMenuItem("��ֵ����", "content-1-3-1.htm", "content"));
chap_1_3.addItem(new TreeMenuItem("�������", "content-1-3-2.htm", "content"));
chap_1_3.addItem(new TreeMenuItem("����ϰ��", "content-1-3-x.htm", "content"));
chap_1.items[2].makeSubmenu(chap_1_3);


//�ڶ���
var chap_2 = new TreeMenu();
chap_2.addItem(new TreeMenuItem("��һ�� ��������","content-2-1.htm","content"));
chap_2.addItem(new TreeMenuItem("�ڶ��� ����ʽ","content-2-2.htm","content"));
chap_2.addItem(new TreeMenuItem("������ ν������","content-2-3.htm","content"));
treeMenu.items[1].makeSubmenu(chap_2);
//�ڶ��µ�һ��
var chap_2_1 = new TreeMenu();
chap_2_1.addItem(new TreeMenuItem("����", "content-2-1-1.htm", "content"));
chap_2_1.addItem(new TreeMenuItem("ν��", "content-2-1-2.htm", "content"));
chap_2_1.addItem(new TreeMenuItem("����", "content-2-1-3.htm", "content"));
chap_2_1.addItem(new TreeMenuItem("ν�ʹ�ʽ", "content-2-1-4.htm", "content"));
chap_2_1.addItem(new TreeMenuItem("Լ��", "content-2-1-5.htm", "content"));
chap_2_1.addItem(new TreeMenuItem("����ϰ��", "content-2-1-x.htm", "content"));
chap_2.items[0].makeSubmenu(chap_2_1);
//�ڶ��µڶ���
var chap_2_2 = new TreeMenu();
chap_2_2.addItem(new TreeMenuItem("��������", "content-2-2-1.htm", "content"));
chap_2_2.addItem(new TreeMenuItem("����ʽ", "content-2-2-2.htm", "content"));
chap_2_2.addItem(new TreeMenuItem("��ʽ", "content-2-2-3.htm", "content"));
chap_2_2.addItem(new TreeMenuItem("����ϰ��", "content-2-2-x.htm", "content"));
chap_2.items[1].makeSubmenu(chap_2_2);
//�ڶ��µ�����
var chap_2_3 = new TreeMenu();
chap_2_3.addItem(new TreeMenuItem("��������", "content-2-3-1.htm", "content"));
chap_2_3.addItem(new TreeMenuItem("�������", "content-2-3-2.htm", "content"));
chap_2_3.addItem(new TreeMenuItem("����ϰ��", "content-2-3-x.htm", "content"));
chap_2.items[2].makeSubmenu(chap_2_3);

//������
var chap_3 = new TreeMenu();
chap_3.addItem(new TreeMenuItem("��һ�� ��������","content-3-1.htm","content"));
chap_3.addItem(new TreeMenuItem("�ڶ��� ���ϴ���","content-3-2.htm","content"));
chap_3.addItem(new TreeMenuItem("������ �ѿ����˻�","content-3-3.htm","content"));
treeMenu.items[2].makeSubmenu(chap_3);
//�����µ�һ��
var chap_3_1 = new TreeMenu();
chap_3_1.addItem(new TreeMenuItem("����", "content-3-1-1.htm", "content"));
chap_3_1.addItem(new TreeMenuItem("Ԫ��", "content-3-1-2.htm", "content"));
chap_3_1.addItem(new TreeMenuItem("���⼯��", "content-3-1-3.htm", "content"));
chap_3_1.addItem(new TreeMenuItem("���ϼ�Ĺ�ϵ", "content-3-1-4.htm", "content"));
chap_3_1.addItem(new TreeMenuItem("����ϰ��", "content-3-1-x.htm", "content"));
chap_3.items[0].makeSubmenu(chap_3_1);
//�����µڶ���
var chap_3_2 = new TreeMenu();
chap_3_2.addItem(new TreeMenuItem("���ϵ�����", "content-3-2-1.htm", "content"));
chap_3_2.addItem(new TreeMenuItem("���ϴ���", "content-3-2-2.htm", "content"));
chap_3_2.addItem(new TreeMenuItem("����ϰ��", "content-3-2-x.htm", "content"));
chap_3.items[1].makeSubmenu(chap_3_2);
//�����µ�����
var chap_3_3 = new TreeMenu();
chap_3_3.addItem(new TreeMenuItem("��ż", "content-3-3-1.htm", "content"));
chap_3_3.addItem(new TreeMenuItem("�ѿ����˻�", "content-3-3-2.htm", "content"));
chap_3_3.addItem(new TreeMenuItem("����ϰ��", "content-3-3-x.htm", "content"));
chap_3.items[2].makeSubmenu(chap_3_3);

//������
var chap_4 = new TreeMenu();
chap_4.addItem(new TreeMenuItem("��һ�� ��ϵ","content-4-1.htm","content"));
chap_4.addItem(new TreeMenuItem("�ڶ��� �ȼ۹�ϵ","content-4-2.htm","content"));
chap_4.addItem(new TreeMenuItem("������ ��ϵ�ĺϳ�","content-4-3.htm","content"));
treeMenu.items[3].makeSubmenu(chap_4);
//�����µ�һ��
var chap_4_1 = new TreeMenu();
chap_4_1.addItem(new TreeMenuItem("��������", "content-4-1-1.htm", "content"));
chap_4_1.addItem(new TreeMenuItem("��������", "content-4-1-2.htm", "content"));
chap_4_1.addItem(new TreeMenuItem("��ϵ�ı�ʾ", "content-4-1-3.htm", "content"));
chap_4_1.addItem(new TreeMenuItem("����ϰ��", "content-4-1-x.htm", "content"));
chap_4.items[0].makeSubmenu(chap_4_1);
//�����µڶ���
var chap_4_2 = new TreeMenu();
chap_4_2.addItem(new TreeMenuItem("�ȼ۹�ϵ", "content-4-2-1.htm", "content"));
chap_4_2.addItem(new TreeMenuItem("����", "content-4-2-2.htm", "content"));
chap_4_2.addItem(new TreeMenuItem("�ɵȼ�������", "content-4-2-3.htm", "content"));
chap_4_2.addItem(new TreeMenuItem("�ɻ��ֶ���ȼ�", "content-4-2-4.htm", "content"));
chap_4_2.addItem(new TreeMenuItem("����ϰ��", "content-4-2-x.htm", "content"));
chap_4.items[1].makeSubmenu(chap_4_2);
//�����µ�����
var chap_4_3 = new TreeMenu();
chap_4_3.addItem(new TreeMenuItem("��ϵ�ĺϳ�", "content-4-3-1.htm", "content"));
chap_4_3.addItem(new TreeMenuItem("�ϳɵı�ʾ", "content-4-3-2.htm", "content"));
chap_4_3.addItem(new TreeMenuItem("��ϵ����", "content-4-3-3.htm", "content"));
chap_4_3.addItem(new TreeMenuItem("����ϰ��", "content-4-3-x.htm", "content"));
chap_4.items[2].makeSubmenu(chap_4_3);


//������
var chap_5 = new TreeMenu();
chap_5.addItem(new TreeMenuItem("��һ�� ��������","content-5-1.htm","content"));
chap_5.addItem(new TreeMenuItem("�ڶ��� ��Ҫ����","content-5-2.htm","content"));
chap_5.addItem(new TreeMenuItem("������ ������","content-5-3.htm","content"));
chap_5.addItem(new TreeMenuItem("���Ľ� �û�","content-5-4.htm","content"));
chap_5.addItem(new TreeMenuItem("����� ��Ԫ����","content-5-5.htm","content"));
treeMenu.items[4].makeSubmenu(chap_5);
//�����µ�һ��
var chap_5_1 = new TreeMenu();
chap_5_1.addItem(new TreeMenuItem("��������", "content-5-1-1.htm", "content"));
chap_5_1.addItem(new TreeMenuItem("������Ĺ�ϵ", "content-5-1-2.htm", "content"));
chap_5_1.addItem(new TreeMenuItem("����ϰ��", "content-5-1-x.htm", "content"));
chap_5.items[0].makeSubmenu(chap_5_1);
//�����µڶ���
var chap_5_2 = new TreeMenu();
chap_5_2.addItem(new TreeMenuItem("��һ��", "content-5-2-1.htm", "content"));
chap_5_2.addItem(new TreeMenuItem("�ڶ���", "content-5-2-2.htm", "content"));
chap_5_2.addItem(new TreeMenuItem("������", "content-5-2-3.htm", "content"));
chap_5_2.addItem(new TreeMenuItem("������", "content-5-2-4.htm", "content"));
chap_5_2.addItem(new TreeMenuItem("����ϰ��", "content-5-2-x.htm", "content"));
chap_5.items[1].makeSubmenu(chap_5_2);
//�����µ�����
var chap_5_3 = new TreeMenu();
chap_5_3.addItem(new TreeMenuItem("������", "content-5-3-1.htm", "content"));
chap_5_3.addItem(new TreeMenuItem("����ϰ��", "content-5-3-x.htm", "content"));
chap_5.items[2].makeSubmenu(chap_5_3);
//�����µ��Ľ�
var chap_5_4 = new TreeMenu();
chap_5_4.addItem(new TreeMenuItem("�û�", "content-5-4-1.htm", "content"));
chap_5_4.addItem(new TreeMenuItem("����ϰ��", "content-5-4-x.htm", "content"));
chap_5.items[3].makeSubmenu(chap_5_4);
//�����µ����
var chap_5_5 = new TreeMenu();
chap_5_5.addItem(new TreeMenuItem("��Ԫ����", "content-5-5-1.htm", "content"));
chap_5_5.addItem(new TreeMenuItem("��λԪ", "content-5-5-2.htm", "content"));
chap_5_5.addItem(new TreeMenuItem("��Ԫ", "content-5-5-3.htm", "content"));
chap_5_5.addItem(new TreeMenuItem("��Ԫ", "content-5-5-4.htm", "content"));
chap_5_5.addItem(new TreeMenuItem("����ϰ��", "content-5-5-x.htm", "content"));
chap_5.items[4].makeSubmenu(chap_5_5);

//������
var chap_6 = new TreeMenu();
chap_6.addItem(new TreeMenuItem("��һ�� �����ṹ","content-6-1.htm","content"));
chap_6.addItem(new TreeMenuItem("�ڶ��� ����ϵͳ��Ĺ�ϵ","content-6-2.htm","content"));
chap_6.addItem(new TreeMenuItem("������ Ⱥ���","content-6-3.htm","content"));
treeMenu.items[5].makeSubmenu(chap_6);
//�����µ�һ��
var chap_6_1 = new TreeMenu();
chap_6_1.addItem(new TreeMenuItem("����","content-6-1-1.htm","content"));
chap_6_1.addItem(new TreeMenuItem("ʵ��","content-6-1-2.htm","content"));
chap_6.items[0].makeSubmenu(chap_6_1);
//�����µڶ���
var chap_6_2 = new TreeMenu();
chap_6_2.addItem(new TreeMenuItem("ͬһ����", "content-6-2-1.htm", "content"));
chap_6_2.addItem(new TreeMenuItem("�Ӵ���", "content-6-2-2.htm", "content"));
chap_6_2.addItem(new TreeMenuItem("̬ͬ��ϵ", "content-6-2-3.htm", "content"));
chap_6_2.addItem(new TreeMenuItem("�̴���", "content-6-2-4.htm", "content"));
chap_6_2.addItem(new TreeMenuItem("������", "content-6-2-5.htm", "content"));
chap_6.items[1].makeSubmenu(chap_6_2);
//�����µ�����
//var chap_6_3 = new TreeMenu();
//chap_6_3.addItem(new TreeMenuItem("����", "content-6-3-1.htm", "content"));
//chap_6_3.addItem(new TreeMenuItem("Ӧ��", "content-6-3-2.htm", "content"));
//chap_6.items[2].makeSubmenu(chap_6_3);

