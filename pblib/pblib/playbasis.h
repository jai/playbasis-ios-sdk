//
//  playbasis.h
//  playbasis
//
//  Created by Playbasis.
//  Copyright (c) 2556 Playbasisß. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum
{
    Started,
    ResponseReceived,
    ReceivingData,
    FinishedWithError,
    Finished
}
PBRequestState;

@protocol PBResponseHandler <NSObject>
-(void)processResponse:(NSDictionary*)jsonResponse withURL:(NSURL *)url;
@end

@interface PBRequest : NSObject
{
    NSURL* url;
    NSMutableData *receivedData;
    NSDictionary *jsonResponse;
    PBRequestState state;
    id<PBResponseHandler> responseDelegate;
}
-(id)initWithURLRequest:(NSURLRequest *)request;
-(id)initWithURLRequest:(NSURLRequest *)request andDelegate:(id<PBResponseHandler>)delegate;
-(void)dealloc;
-(PBRequestState)getRequestState;
-(NSDictionary *)getResponse;

-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
-(void)connectionDidFinishLoading:(NSURLConnection *)connection;
@end

@interface Playbasis : NSObject
{
    NSString *token;
    NSString *apiKeyParam;
    id<PBResponseHandler> authDelegate;
}

+ (instancetype)sharedInstance;

-(id)init;
-(void)dealloc;

-(PBRequest *)auth:(NSString *)apiKey :(NSString *)apiSecret :(id<PBResponseHandler>)delegate;
-(PBRequest *)renew:(NSString *)apiKey :(NSString *)apiSecret :(id<PBResponseHandler>)delegate;
-(PBRequest *)player:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)playerList:(NSString *)playerListId :(id<PBResponseHandler>)delegate;
-(PBRequest *)playerDetail:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)registerUser:(NSString *)playerId :(id<PBResponseHandler>)delegate :(NSString *)username :(NSString *)email :(NSString *)imageUrl, ...;
-(PBRequest *)updateUser:(NSString *)playerId :(id<PBResponseHandler>)delegate :(NSString *)firstArg ,...;
-(PBRequest *)deleteUser:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)login:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)logout:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)points:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)point:(NSString *)playerId :(NSString *)pointName :(id<PBResponseHandler>)delegate;
-(PBRequest *)pointHistory:(NSString *)playerId :(NSString *)pointName :(unsigned int)offset :(unsigned int)limit :(id<PBResponseHandler>)delegate;
-(PBRequest *)actionLastPerformed:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)actionLastPerformedTime:(NSString *)playerId :(NSString *)actionName :(id<PBResponseHandler>)delegate;
-(PBRequest *)actionPerformedCount:(NSString *)playerId :(NSString *)actionName :(id<PBResponseHandler>)delegate;
-(PBRequest *)badgeOwned:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)rank:(NSString *)rankedBy :(unsigned int)limit :(id<PBResponseHandler>)delegate;
-(PBRequest *)ranks:(unsigned int)limit :(id<PBResponseHandler>)delegate;
-(PBRequest *)level:(unsigned int)level :(id<PBResponseHandler>)delegate;
-(PBRequest *)levels:(id<PBResponseHandler>)delegate;
-(PBRequest *)claimBadge:(NSString *)playerId :(NSString *)badgeId :(id<PBResponseHandler>)delegate;
-(PBRequest *)redeemBadge:(NSString *)playerId :(NSString *)badgeId :(id<PBResponseHandler>)delegate;
-(PBRequest *)goodsOwned:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)questOfPlayer:(NSString *)playerId :(NSString *)questId :(id<PBResponseHandler>)delegate;
-(PBRequest *)questListOfPlayer:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)badge:(NSString *)badgeId :(id<PBResponseHandler>)delegate;
-(PBRequest *)badges :(id<PBResponseHandler>)delegate;
-(PBRequest *)goods:(NSString *)goodId :(id<PBResponseHandler>)delegate;
-(PBRequest *)goodsList :(id<PBResponseHandler>)delegate;
-(PBRequest *)actionConfig :(id<PBResponseHandler>)delegate;
-(PBRequest *)rule:(NSString *)playerId :(NSString *)action :(id<PBResponseHandler>)delegate, ...;
-(PBRequest *)quests:(id<PBResponseHandler>)delegate;
-(PBRequest *)quest:(NSString *)questId :(id<PBResponseHandler>)delegate;
-(PBRequest *)mission:(NSString *)questId :(NSString *)missionId :(id<PBResponseHandler>)delegate;
-(PBRequest *)questAvailable:(NSString *)questId :(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)questsAvailable:(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)joinQuest:(NSString *)questId :(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)cancelQuest:(NSString *)questId :(NSString *)playerId :(id<PBResponseHandler>)delegate;
-(PBRequest *)redeemGoods:(NSString *)goodsId :(NSString *)playerId :(unsigned int)amount :(id<PBResponseHandler>)delegate;
-(PBRequest *)recentPoint:(unsigned int)offset :(unsigned int)limit :(id<PBResponseHandler>)delegate;
-(PBRequest *)recentPointByName:(NSString *)pointName :(unsigned int)offset :(unsigned int)limit :(id<PBResponseHandler>)delegate;
-(PBRequest *)call:(NSString *)method withData:(NSString *)data andDelegate:(id<PBResponseHandler>)delegate;
@end
