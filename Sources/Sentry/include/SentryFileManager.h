#import <Foundation/Foundation.h>

#import "SentryCurrentDateProvider.h"
#import "SentryDefines.h"
#import "SentrySession.h"

NS_ASSUME_NONNULL_BEGIN

@class SentryEvent, SentryDsn, SentryEnvelope, SentryFileContents;

NS_SWIFT_NAME(SentryFileManager)
@interface SentryFileManager : NSObject
SENTRY_NO_INIT

- (_Nullable instancetype)initWithDsn:(SentryDsn *)dsn
               andCurrentDateProvider:(id<SentryCurrentDateProvider>)currentDateProvider
                     didFailWithError:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSString *)storeEnvelope:(SentryEnvelope *)envelope;

- (void)storeCurrentSession:(SentrySession *)session;
- (SentrySession *_Nullable)readCurrentSession;
- (void)deleteCurrentSession;

- (void)storeTimestampLastInForeground:(NSDate *)timestamp;
- (NSDate *_Nullable)readTimestampLastInForeground;
- (void)deleteTimestampLastInForeground;

+ (BOOL)createDirectoryAtPath:(NSString *)path withError:(NSError **)error;

- (void)deleteAllEnvelopes;

- (void)deleteAllFolders;

- (NSArray<SentryFileContents *> *)getAllEnvelopes;

- (BOOL)removeFileAtPath:(NSString *)path;

- (NSArray<NSString *> *)allFilesInFolder:(NSString *)path;

- (NSString *)storeDictionary:(NSDictionary *)dictionary toPath:(NSString *)path;

@property (nonatomic, assign) NSUInteger maxEnvelopes;

@end

NS_ASSUME_NONNULL_END
