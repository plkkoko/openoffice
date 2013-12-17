/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef INCLUDED_SLIDESHOW_ANIMATIONEVENTHANDLER_HXX
#define INCLUDED_SLIDESHOW_ANIMATIONEVENTHANDLER_HXX

#include <boost/shared_ptr.hpp>
#include "animationnode.hxx"


/* Definition of AnimationEventHandler interface */

namespace slideshow
{
    namespace internal
    {

        /** Interface for handling animation events.

        	Classes implementing this interface can be added to an
        	EventMultiplexer object, and are called from there to
        	handle animation state change events.
         */
        class AnimationEventHandler
        {
        public:
            virtual ~AnimationEventHandler() {}

            /** Handle the event.

            	@param rNode
                Animation node which caused this event to fire

            	@return true, if this handler has successfully
            	processed the animation event. When this method
            	returns false, possibly other, less prioritized
            	handlers are called, too.
             */
            virtual bool handleAnimationEvent( const AnimationNodeSharedPtr& rNode ) = 0;
        };

        typedef ::boost::shared_ptr< AnimationEventHandler > AnimationEventHandlerSharedPtr;

    }
}

#endif /* INCLUDED_SLIDESHOW_ANIMATIONEVENTHANDLER_HXX */