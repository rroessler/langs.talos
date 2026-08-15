/// Package Modules
import { Icon } from '../icon';
import { Anchor } from '../anchor';
import { Fragment } from '../fragment';

/** Portal Component. */
export interface Portal extends Portal.Props {}
export function Portal({ name, href, icon, description }: Portal) {
    // rebuild the header prefix now
    const prefix = Icon.Dynamic(icon, { size: 20 });

    // prepare the header to be used now
    const header = [<Fragment key="icon" children={prefix} />, <Fragment key="name" children={name} />];

    // and construct the resulting portal now
    return (
        <Anchor sleek href={href} className="bg-fd-card rounded-2xl border shadow-lg px-4 py-6">
            <h2 className="flex items-center gap-2 mt-0 mb-2 font-medium" children={header} />
            <p className="text-sm text-fd-muted-foreground mt-2 mb-0" children={description} />
        </Anchor>
    );
}

export namespace Portal {
    //  TYPEDEFS  //

    /** Portal Component Properties. */
    export type Props = {
        icon?: Icon.Name;
        href: string;
        name: React.ReactNode;
        description?: React.ReactNode;
    };
}
