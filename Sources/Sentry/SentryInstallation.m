#import "SentryInstallation.h"
#import "SentryDefines.h"
#import "SentryOptions.h"

NS_ASSUME_NONNULL_BEGIN

@implementation SentryInstallation

static NSString *volatile installationString;

+ (NSString *)idWithOptions:(SentryOptions *)options
{
    if (nil != installationString) {
        return installationString;
    }
    @synchronized(self) {
        if (nil != installationString) {
            return installationString;
        }

        NSString *cachePath = options.cacheDirectoryPath;
        NSString *installationFilePath = [cachePath stringByAppendingPathComponent:@"INSTALLATION"];
        NSData *installationData = [NSData dataWithContentsOfFile:installationFilePath];

        if (nil == installationData) {
            installationString = [NSUUID UUID].UUIDString;
            NSData *installationStringData =
                [installationString dataUsingEncoding:NSUTF8StringEncoding];
            NSFileManager *fileManager = [NSFileManager defaultManager];
            [fileManager createFileAtPath:installationFilePath
                                 contents:installationStringData
                               attributes:nil];
        } else {
            installationString = [[NSString alloc] initWithData:installationData
                                                       encoding:NSUTF8StringEncoding];
        }

        return installationString;
    }
}

@end

NS_ASSUME_NONNULL_END
