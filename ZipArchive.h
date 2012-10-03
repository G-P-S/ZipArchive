//
//  ZipArchive.h
//  
//
//  Created by aish on 08-9-11.
//  acsolu@gmail.com
//  Copyright 2008  Inc. All rights reserved.
//
// History: 
//    09-11-2008 version 1.0    release
//    10-18-2009 version 1.1    support password protected zip files
//    10-21-2009 version 1.2    fix date bug

#include "minizip/zip.h"
#include "minizip/unzip.h"


@protocol ZipArchiveDelegate <NSObject>
@optional
-(void) ErrorMessage:(NSString*) msg;
-(BOOL) OverWriteOperation:(NSURL*) file;

@end


@interface ZipArchive : NSObject {
@private
	zipFile		_zipFile;
	unzFile		_unzFile;
	
	NSString*   _password;
	id			_delegate;
}

@property (nonatomic, retain) id delegate;

-(BOOL) CreateZipFile2:(NSString*) zipFile;
-(BOOL) CreateZipFile2:(NSString*) zipFile Password:(NSString*) password;
-(BOOL) addFileToZip:(NSString*) file newname:(NSString*) newname;
-(BOOL) CloseZipFile2;

/**
 @brief Open a zip file for unarchiving
 @param zipFileURL - URL of the file.  Use URL for sanboxing
 
 @returns YES if open, NO if not.
 **/
-(BOOL) UnzipOpenFile:(NSURL *) zipFileURL;
/**
 @brief Open a password protected zip file for unarchiving
 @param zipFileURL - URL of the file.  Use URL for sanboxing
 @param password - password that is protecting the file.
 
 @returns YES if open, NO if not.
 **/
-(BOOL) UnzipOpenFile:(NSURL *) zipFileURL 
			 Password:(NSString*) password;
/**
 @brief Unzip the currently open file to the destination URL
 
 The destination should be a folder since the zip file can contain multiple files.  For each file in the zip package,
 unzip the file to the destination folder.  Use the statusDisplay callback to inform the caller of the unzip status,
 cancel the unzip process if the callback block returns a NO
 
 @param destinationURL - URL of the destination folder
 @param overWrite - YES if existing files in the folder are to be overwritten
 @param statusDisplay - Block to show the status and return if cancel is pressed
 @returns YES if successful
 **/
-(BOOL) UnzipFileTo:(NSURL *) destinationURL 
		  overWrite:(BOOL) overwrite 
	  statusDisplay:(BOOL (^)(float percentDone))statusDisplay;
-(BOOL) UnzipCloseFile;
-(UInt64) UnzipFileSize;
@end
