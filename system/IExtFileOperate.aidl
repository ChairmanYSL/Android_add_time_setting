package com.xgd.smartpos.manager.system;


interface IExtFileOperate {
	//拷贝文件，destFileName必须是SD卡中的文件
	boolean copyFile(String srcFileName, String destFileName, boolean overlay);
	//删除文件，必须是SD卡中的文件
	boolean deleteFile(String filePath);
	//删除文件夹以及目录下的文件，必须是SD卡中的文件夹
	boolean deleteDirectory(String filePath);
	//根据路径删除指定的目录或文件，无论存在与否，必须是SD卡中的目录或文件
	boolean DeleteFolder(String filePath);
}
